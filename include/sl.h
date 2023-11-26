/**
 * (c) 2023 David Rowbotham thedaver64@gmail.com
*/
#pragma once

#include <cstdint>
#define FN_USE_DOUBLES
#include "fastnoise.h"

/**
 * Bits and bobs that need to be available everywhere. 
 * 
*/
#ifdef _WIN32
#include "resource.h"
#endif
#include "glm/glm.hpp"

#ifndef GLuint
typedef unsigned int GLuint;
#endif

#ifndef GLRef
typedef unsigned int GLRef;
#endif

#ifndef GLenum
	typedef unsigned int GLenum;
#endif
using glm::vec2;
using glm::vec3;
using glm::vec4;
using glm::mat4x4;
using glm::dvec2;
using glm::dvec3;
using glm::dvec4;
using glm::dmat4x4;

class quat {

};

class dquat {

};

class polar {
public:
	union
	{
		float d[4] = { 0,0,0,0 };
		struct { float ra, dec, rad, w; };
		struct { float lon, lat, alt, p; };
	};
	polar(const float& lon = 0,
		const float& lat = 0,
		const float& alt = 0);
	polar(const float p[3]);
	polar(const vec3& pos);
	float& operator[](size_t index);
	vec3 polar_to_cartesian(const polar& pos);
	polar cartesian_to_polar(const vec3& pos);
	vec3 to_cartesian();
	void from_cartesian(const vec3& pos);
};

class dpolar {
public:
	union
	{
		double d[4] = { 0,0,0,0 };
		struct { double ra, dec, rad, w; };
		struct { double lon, lat, alt, p; };
	};
	dpolar(const double& lon = 0,
		const double& lat = 0,
		const double& alt = 0);
	dpolar(const double p[3]);
	dpolar(const dvec3& pos);
	double& operator[](size_t index);
	dvec3 polar_to_cartesian(const dpolar& pos);
	dpolar cartesian_to_polar(const dvec3& pos);
	dvec3 to_cartesian();
	void from_cartesian(const vec3& pos);
};

#define sgn(x) ((x<0)?-1:((x>0)?1:0))
#define argb(a,r,g,b) ( ((uint32_t)(a)<<24) |		\
			((((uint32_t)r)<<24)>>8) |	\
			((((uint32_t)g)<<24)>>16) |	\
			((((uint32_t)b)<<24)>>24))

#define rgb(r,g,b) argb(255,(r),(g),(b))
#define argb_f(a,r,g,b) argb((uint8_t)((a)*255.0f),(uint8_t)((r)*255.0f),(uint8_t)((g)*255.0f),(uint8_t)((b)*255.0f))
#define rgb_f(r,g,b) argb_f(1.0f,(r),(g),(b))
#define geta(p) ((uint32_t)((p))>>24)
#define getr(p) (((uint32_t)((p))<<8)>>24)
#define getg(p) (((uint32_t)((p))<<16)>>24)
#define getb(p) (((uint32_t)((p))<<24)>>24)

#define geta_nf(p) (geta(p)/255.0f)
#define getr_nf(p) (getr(p)/255.0f)
#define getg_nf(p) (getg(p)/255.0f)
#define getb_nf(p) (getb(p)/255.0f)
template<typename T, typename U, typename V>
inline T clamp(T a, U low, V high)
{
	T val = a < low ? low : a;
	return val > high ? high : val;
}
typedef int8_t int8;
typedef uint8_t uint8;
typedef int16_t int16;
typedef uint16_t uint16;
typedef int32_t int32;
typedef uint32_t uint32;
typedef int64_t int64;
typedef uint64_t uint64;
typedef uint32_t pixel32;

int main_audio();
int main_graphics();
int main_networking();

struct SLContext;
class Texture;
extern "C" {
void sl_load_gl_extensions();
}

int32 sl_create_context(SLContext **context,const char *titletext,int32 width,int32 height,bool fullscreen);
int32 sl_destroy_context(SLContext **context);
bool sl_want_to_quit(SLContext *context);
void sl_quit(SLContext *context);
void sl_swap(SLContext *context);
void sl_poll_input(SLContext *context);
void sl_process_input(SLContext *context);