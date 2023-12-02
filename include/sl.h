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



#ifndef GLuint
typedef unsigned int GLuint;
#endif

#ifndef GLRef
typedef unsigned int GLRef;
#endif

#ifndef GLenum
	typedef unsigned int GLenum;
#endif

#include "sl_maths.h"
#include "sl_argb.h"


struct SLContext;
class SLTexture;
class SLTextureAtlas;
class SLFrameBuffer;
class SLPrimitiveBuffer;
class SLShader;
class SLCamera;

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

int main_audio();
int main_networking();

void render_gui();
void update_gui();
void init_gui(SLContext *context);

int32 string_split_c(const char *txt, char delim, char ***tokens);
char *load_text_file(const char *filename, int32 &num_bytes_read);

