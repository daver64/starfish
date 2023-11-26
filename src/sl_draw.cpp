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
#include <GL/glext.h>
#endif

#include "sl_context.h"
#include "sl_draw.h"
#include "sl_texture.h"
#include <cassert>

void sl_clrscr(SLContext *context,pixel32 colour)
{
    float r=getr_nf(colour);
    float g=getg_nf(colour);
    float b=getb_nf(colour);
    glClearColor(r,g,b,0);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
}

void sl_clrscr(SLContext *context)
{
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
}

void sl_clearcolour(SLContext *context,pixel32 colour)
{
    float r=getr_nf(colour);
    float g=getg_nf(colour);
    float b=getb_nf(colour);
    glClearColor(r,g,b,0);
}
 
void sl_ortho2d(SLContext *context)
{
    glViewport(0, 0, context->width, context->height);
}
void sl_putpixel(SLTexture *target,int32 x,int32 y, pixel32 colour)
{
    assert(x>=0 && x<target->width);
    assert(y>=0 && y<target->height);
    target->pixeldata[y*target->width+x]=colour;
}
pixel32 sl_getpixel(SLTexture *target,int32 x,int32 y)
{
    assert(x>=0 && x<target->width);
    assert(y>=0 && y<target->height);
    return target->pixeldata[y*target->width+x];
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
void sl_material_ambient(float_t* values)
{
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, values);
}
void sl_material_diffuse(float_t* values)
{
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, values);
}
void sl_material_emissive(float_t* values)
{
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, values);
}
void sl_material_specular(float_t* values)
{
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, values);
}
void sl_material_shininess(float_t* value)
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
