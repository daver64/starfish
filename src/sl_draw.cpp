/**
 * (c) 2023 David Rowbotham thedaver64@gmail.com
*/
#ifdef _WIN32
#include <windows.h>
#undef max
#undef min

#include <GL/GL.h>
#include <GL/GLU.h>
#include "sl_glext.h"
#else
#define GL_GLEXT_PROTOTYPES

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glext.h>
#endif

#include "sl_context.h"
#include "sl_draw.h"
#include "sl_texture.h"
#include "sl_primitivebuffer.h"
#include <cassert>

void sl_clrscr(SLContext *context, pixel32 colour)
{
	float r = getr_nf(colour);
	float g = getg_nf(colour);
	float b = getb_nf(colour);
	glClearColor(r, g, b, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void sl_clrscr(SLContext *context)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void sl_clearcolour(SLContext *context, pixel32 colour)
{
	float r = getr_nf(colour);
	float g = getg_nf(colour);
	float b = getb_nf(colour);
	glClearColor(r, g, b, 0);
}

void sl_putpixel(SLTexture *target, int32 x, int32 y, pixel32 colour)
{
	assert(x >= 0 && x < target->width);
	assert(y >= 0 && y < target->height);
	target->pixeldata[y * target->width + x] = colour;
}
pixel32 sl_getpixel(SLTexture *target, int32 x, int32 y)
{
	assert(x >= 0 && x < target->width);
	assert(y >= 0 && y < target->height);
	return target->pixeldata[y * target->width + x];
}


void sl_begin_triangles(SLPrimitiveBuffer *target)
{
	target->begin(GL_TRIANGLES);
}
void sl_end_triangles(SLPrimitiveBuffer *target)
{
	target->end();
}
void sl_begin_lines(SLPrimitiveBuffer *target)
{
	target->begin(GL_LINES);
}
void sl_end_lines(SLPrimitiveBuffer *target)
{
	target->end();
}
void sl_begin_quads(SLPrimitiveBuffer *target)
{
	target->begin(GL_QUADS);
}
void sl_end_quads(SLPrimitiveBuffer *target)
{
	target->end();
}
void sl_triangle(SLPrimitiveBuffer *target,
					 float32 x1, float32 y1,
					 float32 x2, float32 y2,
					 float32 x3, float32 y3, pixel32 colour)
{
	target->colour(colour);
	target->vertex(vec2(x1, y1));
	target->vertex(vec2(x2, y2));
	target->vertex(vec2(x3, y3));
}

void sl_triangle(SLPrimitiveBuffer *target,
					 float32 x1, float32 y1,
					 float32 x2, float32 y2,
					 float32 x3, float32 y3,
					 pixel32 colour1, pixel32 colour2, pixel32 colour3)
{
	target->colour(colour1);
	target->vertex(vec2(x1, y1));
	target->colour(colour2);
	target->vertex(vec2(x2, y2));
	target->colour(colour3);
	target->vertex(vec2(x3, y3));
}
void sl_rectangle(SLPrimitiveBuffer *target,
				  float32 x, float32 y, 
				  float32 width, float32 height, 
				  pixel32 colour)
{
	const float32 x2 = x + width;
	const float32 y2 = y + height;

	target->colour(colour);

	target->texcoord0(vec2(0, 0));
	target->vertex(vec2(x, y));

	target->texcoord0(vec2(1, 0));
	target->vertex(vec2(x2, y));

	target->texcoord0(vec2(1, 1));
	target->vertex(vec2(x2, y2));

	target->texcoord0(vec2(0, 1));
	target->vertex(vec2(x, y2));	
}
