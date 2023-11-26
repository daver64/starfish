/**
 * (c) 2023 David Rowbotham thedaver64@gmail.com and Toni Ylisirniö 
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

void matrix_apply(mat4x4 &m)
{
    glMultMatrixf((GLfloat*)&m[0]);
}
void sl_projection(int32 width, int32 height, float32 fov, float32 nearz, float32 farz)
{
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(fov, (float32)width / (float32)height, nearz, farz);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
void sl_rotate_x(float64 angle)
{
	glRotated(angle, 1, 0, 0);
}
void sl_rotate_y(float64 angle)
{
	glRotated(angle, 0, 1, 0);
}
void sl_rotate_z(float64 angle)
{
	glRotated(angle, 0, 0, 1);
}
void sl_rotate_x(float32 angle)
{
	glRotatef(angle, 1, 0, 0);
}
void sl_rotate_y(float32 angle)
{
	glRotatef(angle, 0, 1, 0);
}
void sl_rotate_z(float32 angle)
{
	glRotatef(angle, 0, 0, 1);
}
void sl_translatef(float32 x, float32 y, float32 z)
{
	glTranslatef(x, y, z);
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
void sl_ortho(int32 width,int32 height, bool flip, float64 near_z, float64 far_z)
{
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (!flip)
		glOrtho(0, width, height, 0, near_z, far_z);
	else
		glOrtho(0, width, 0, height, near_z, far_z);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void sl_ortho(SLContext *context, bool flip, float64 near_z, float64 far_z)
{
    sl_ortho(context->width,context->height,flip,near_z,far_z);
}
