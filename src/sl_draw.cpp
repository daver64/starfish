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
void sl_push_matrix()
{
	glPushMatrix();
}
void sl_pop_matrix()
{
	glPopMatrix();
}
void sl_lookat(vec3 eye, vec3 center, vec3 up)
{
	gluLookAt(eye.x, eye.y, eye.z + 0.001,
		center.x, center.y, center.z,
		up.y, up.x, up.z);
}
void sl_translate(dvec3 pos)
{
	glTranslated(pos.x, pos.y, pos.z);
}
void sl_translate(vec3 pos)
{
	glTranslatef(pos.x, pos.y, pos.z);
}
void sl_translate(ivec3 pos)
{
	glTranslatef((GLfloat)pos.x, (GLfloat)pos.y, (GLfloat)pos.z);
}
 
void sl_bind_texture(SLPrimitiveBuffer *target,SLTexture *texture)
{
	target->bind_tex0(texture->glref);
	glBindTexture(GL_TEXTURE_2D, texture->glref);
}	
void sl_unbind_texture(SLPrimitiveBuffer *target)
{
	target->bind_tex0(0);
	glBindTexture(GL_TEXTURE_2D,0);
}

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

void sl_ortho(SLContext *context, bool flip, float64 near_z, float64 far_z)
{
	glViewport(0, 0, context->width, context->height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (!flip)
		glOrtho(0, context->width, context->height, 0, near_z, far_z);
	else
		glOrtho(0, context->width, 0, context->height, near_z, far_z);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
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

void sl_enable_arrays()
{
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
}
void sl_disable_arrays()
{
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}
void sl_cull_back()
{
	sl_enable_cull_face();
	glCullFace(GL_BACK);
}
void sl_cull_front()
{
	sl_enable_cull_face();
	glCullFace(GL_FRONT);
}
void sl_disable_cull_face()
{
	glDisable(GL_CULL_FACE);
}
void sl_enable_cull_face()
{
	glEnable(GL_CULL_FACE);
}
void sl_front_cw()
{
	glFrontFace(GL_CW);
}
void sl_front_ccw()
{
	glFrontFace(GL_CCW);
}
void sl_matrix_projection()
{
	glMatrixMode(GL_PROJECTION);
}
void sl_matrix_modelview()
{
	glMatrixMode(GL_MODELVIEW);
}
void sl_load_identity()
{
	glLoadIdentity();
}
void sl_enable_texturing()
{
	glEnable(GL_TEXTURE_2D);
}
void sl_disable_texturing()
{
	glDisable(GL_TEXTURE_2D);
}
void sl_enable_blending()
{
	glEnable(GL_BLEND);
}
void sl_blend_src_alpha_one_minus()
{
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}
void sl_blend_alpha_saturate_one()
{
	glBlendFunc(GL_SRC_ALPHA_SATURATE, GL_ONE);
}
void sl_blend_one_one()
{
	glBlendFunc(GL_ONE, GL_ONE);
}
void sl_blend_src_alpha_one()
{
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
}
void sl_disable_blending()
{
	glDisable(GL_BLEND);
}
void sl_enable_alpha(float_t v)
{
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, v);
}
void sl_disable_alpha()
{
	glDisable(GL_ALPHA_TEST);
}
void sl_enable_depthtest()
{
	glEnable(GL_DEPTH_TEST);
}
void sl_disable_depthtest()
{
	glDisable(GL_DEPTH_TEST);
}
void sl_enable_colour_material()
{
	glEnable(GL_COLOR_MATERIAL);
}
void sl_disable_colour_material()
{
	glDisable(GL_COLOR_MATERIAL);
}
void sl_material_ambient(float_t *values)
{
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, values);
}
void sl_material_diffuse(float_t *values)
{
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, values);
}
void sl_material_emissive(float_t *values)
{
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, values);
}
void sl_material_specular(float_t *values)
{
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, values);
}
void sl_material_shininess(float_t *value)
{
	glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, value);
}
void sl_line_width(float_t w)
{
	glLineWidth(w);
}
void sl_point_size(float_t w)
{
	glPointSize(w);
}
void sl_enable_multisample()
{
	glEnable(GL_MULTISAMPLE);
}
void sl_disable_multisample()
{
	glDisable(GL_MULTISAMPLE);
}
void sl_enable_mipmapping()
{
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
}
void sl_disable_mipmapping()
{
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
}
void sl_disable_texture_filtering()
{
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}
void sl_enable_texture_filtering()
{
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
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
