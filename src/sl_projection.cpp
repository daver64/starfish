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
