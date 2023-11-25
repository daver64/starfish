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
