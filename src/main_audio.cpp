#include "starfish.h"
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <AL/al.h>
#include <AL/alc.h>
#include <AL/alext.h>

#ifdef _WIN32
#include <windows.h>

void al_nssleep(unsigned long nsec)
{
    Sleep(nsec / 1000000);
}
#else
#include <climits>
#include <cmath>
#include <sys/time.h>
#include <unistd.h>
#include <time.h>
#include <cerrno>
using std::modf;
using std::sin;
void al_nssleep(unsigned long nsec)
{
    struct timespec ts, rem;
    ts.tv_sec = (time_t)(nsec / 1000000000ul);
    ts.tv_nsec = (long)(nsec & 1000000000ul);
    while (nanosleep(&ts, &rem) != -1 && errno == EINTR)
        ts = rem;
}

#endif

static void list_audio_devices(const ALCchar *devices)
{
    const ALCchar *device = devices, *next = devices + 1;
    size_t len = 0;

    fprintf(stdout, "Devices list:\n");
    fprintf(stdout, "----------\n");
    while (device && *device != '\0' && next && *next != '\0')
    {
        fprintf(stdout, "%s\n", device);
        len = strlen(device);
        device += (len + 1);
        next += (len + 2);
    }
    fprintf(stdout, "----------\n");
}

#ifndef M_PI
#define M_PI (3.14159265358979323846)
#endif

enum WaveType
{
    WT_Sine,
    WT_Square,
    WT_Sawtooth,
    WT_Triangle,
    WT_Impulse,
    WT_WhiteNoise,
};

static const char *GetWaveTypeName(enum WaveType type)
{
    switch (type)
    {
    case WT_Sine:
        return "sine";
    case WT_Square:
        return "square";
    case WT_Sawtooth:
        return "sawtooth";
    case WT_Triangle:
        return "triangle";
    case WT_Impulse:
        return "impulse";
    case WT_WhiteNoise:
        return "noise";
    }
    return "(unknown)";
}

static inline ALuint dither_rng(ALuint *seed)
{
    *seed = (*seed * 96314165) + 907633515;
    return *seed;
}

static void ApplySin(ALfloat *data, ALuint length, ALdouble g, ALuint srate, ALuint freq)
{
    ALdouble cycles_per_sample = (ALdouble)freq / srate;
    ALuint i;
    for (i = 0; i < length; i++)
    {
        ALdouble ival;
        data[i] += (ALfloat)(sin(modf(i * cycles_per_sample, &ival) * 2.0 * M_PI) * g);
    }
}

/* Generates waveforms using additive synthesis. Each waveform is constructed
 * by summing one or more sine waves, up to (and excluding) nyquist.
 */
static ALuint CreateWave(enum WaveType type, ALuint seconds, ALuint freq, ALuint srate,
                         ALfloat gain)
{
    ALuint seed = 22222;
    ALuint num_samples;
    ALuint data_size;
    ALfloat *data;
    ALuint buffer;
    ALenum err;
    ALuint i;

    if (seconds > INT_MAX / srate / sizeof(ALfloat))
    {
        fprintf(stderr, "Too many seconds: %u * %u * %zu > %d\n", seconds, srate, sizeof(ALfloat),
                INT_MAX);
        return 0;
    }

    num_samples = seconds * srate;

    data_size = (ALuint)(num_samples * sizeof(ALfloat));
    data = (ALfloat *)calloc(1, data_size);
    switch (type)
    {
    case WT_Sine:
        ApplySin(data, num_samples, 1.0, srate, freq);
        break;
    case WT_Square:
        for (i = 1; freq * i < srate / 2; i += 2)
            ApplySin(data, num_samples, 4.0 / M_PI * 1.0 / i, srate, freq * i);
        break;
    case WT_Sawtooth:
        for (i = 1; freq * i < srate / 2; i++)
            ApplySin(data, num_samples, 2.0 / M_PI * ((i & 1) * 2 - 1.0) / i, srate, freq * i);
        break;
    case WT_Triangle:
        for (i = 1; freq * i < srate / 2; i += 2)
            ApplySin(data, num_samples, 8.0 / (M_PI * M_PI) * (1.0 - (i & 2)) / (i * i), srate, freq * i);
        break;
    case WT_Impulse:
        /* NOTE: Impulse isn't handled using additive synthesis, and is
         * instead just a non-0 sample. This can be useful to test (other
         * than resampling, the ALSOFT_DEFAULT_REVERB environment variable
         * can test the reverb response).
         */
        data[0] = 1.0f;
        break;
    case WT_WhiteNoise:
        /* NOTE: WhiteNoise is just uniform set of uncorrelated values, and
         * is not influenced by the waveform frequency.
         */
        for (i = 0; i < num_samples; i++)
        {
            ALuint rng0 = dither_rng(&seed);
            ALuint rng1 = dither_rng(&seed);
            data[i] = (ALfloat)(rng0 * (1.0 / UINT_MAX) - rng1 * (1.0 / UINT_MAX));
        }
        break;
    }

    if (gain != 1.0f)
    {
        for (i = 0; i < num_samples; i++)
            data[i] *= gain;
    }

    /* Buffer the audio data into a new buffer object. */
    buffer = 0;
    alGenBuffers(1, &buffer);
    alBufferData(buffer, AL_FORMAT_MONO_FLOAT32, data, (ALsizei)data_size, (ALsizei)srate);
    free(data);

    /* Check if an error occurred, and clean up if so. */
    err = alGetError();
    if (err != AL_NO_ERROR)
    {
        fprintf(stderr, "OpenAL Error: %s\rn", alGetString(err));
        if (alIsBuffer(buffer))
            alDeleteBuffers(1, &buffer);
        return 0;
    }

    return buffer;
}

int main_audio()
{
    ALCdevice *device = NULL;
    device = alcOpenDevice(NULL);
    if (!device)
        fprintf(stdout, "error opening audio device\n");

    list_audio_devices(alcGetString(NULL, ALC_DEVICE_SPECIFIER));
    ALCcontext *context;

    context = alcCreateContext(device, NULL);
    if (!alcMakeContextCurrent(context))
        fprintf(stdout, "error creating context\n");

    ALfloat listenerOri[] = {0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f};
    alListener3f(AL_POSITION, 0, 0, 1.0f);
    alListener3f(AL_VELOCITY, 0, 0, 0);
    alListenerfv(AL_ORIENTATION, listenerOri);

    ALuint source;
    alGenSources((ALuint)1, &source);
    alSourcef(source, AL_PITCH, 1);
    alSourcef(source, AL_GAIN, 1);
    alSource3f(source, AL_POSITION, 0, 0, 0);
    alSource3f(source, AL_VELOCITY, 0, 0, 0);
    alSourcei(source, AL_LOOPING, AL_FALSE);

    ALuint buffer;
    // alGenBuffers((ALuint)1, &buffer);

    ALsizei size, freq;
    ALenum format;
    ALvoid *data;
    ALboolean loop = AL_FALSE;

    enum WaveType wavetype = WT_Sine;
    // const char *appname = argv[0];
    // ALuint source, buffer;
    ALint last_pos;
    ALint seconds = 1;
    ALint srate = 44100;
    ALint tone_freq = 1000;
    // ALCint dev_rate=1000;
    ALenum state;
    ALfloat gain = 1.0f;
    int i;

    /* Load the sound into a buffer. */
    buffer = CreateWave(wavetype, (ALuint)seconds, (ALuint)tone_freq, (ALuint)srate, gain);
    if (!buffer)
    {
        //  CloseAL();
        return 1;
    }

    printf("Playing %dhz %s-wave tone with %dhz sample rate, for %d second%s...\n",
           tone_freq, GetWaveTypeName(wavetype), srate, seconds, (seconds != 1) ? "s" : "");
    fflush(stdout);

    /* Create the source to play the sound with. */
    source = 0;
    alGenSources(1, &source);
    alSourcei(source, AL_BUFFER, (ALint)buffer);
    // assert(alGetError()==AL_NO_ERROR && "Failed to setup sound source");

    /* Play the sound for a while. */
    last_pos = -1;
    alSourcePlay(source);
    do
    {
        ALint pos;
        al_nssleep(10000000);
        alGetSourcei(source, AL_SOURCE_STATE, &state);
        alGetSourcei(source, AL_SAMPLE_OFFSET, &pos);
        pos /= srate;

        if (pos > last_pos)
        {
            last_pos = 0;
            printf("%d...\n", seconds - pos);
            fflush(stdout);
        }
        last_pos = pos;
    } while (alGetError() == AL_NO_ERROR && state == AL_PLAYING);

    /* All done. Delete resources, and close OpenAL. */
    alDeleteSources(1, &source);
    alDeleteBuffers(1, &buffer);

    alcCloseDevice(device);
    /* Close up OpenAL. */
    // CloseAL();

    return 0;
}
