/**
 * (c) 2023 David Rowbotham thedaver64@gmail.com
*/
#pragma once
#include "sl.h"


void sl_push_matrix();
void sl_pop_matrix();
void sl_lookat(vec3 eye, vec3 center, vec3 up);
void sl_translate(dvec3 pos);
void sl_translate(vec3 pos);
void sl_translate(ivec3 pos);
void sl_bind_texture(SLPrimitiveBuffer *target,SLTexture *texture);
void sl_unbind_texture(SLPrimitiveBuffer *target);

void sl_clrscr(SLContext *context,pixel32 colour);
void sl_clrscr(SLContext *context);
void sl_clearcolour(SLContext *context,pixel32 colour);
void sl_ortho(SLContext *context, bool flip = false, float64 near_z = -1.0,float64 far_z = 1.0);
void sl_ortho(int32 width,int32 height, bool flip, float64 near_z, float64 far_z);
void sl_projection(int32 width, int32 height, float32 fov, float32 nearz, float32 farz);
void sl_rotate_x(float64 angle);
void sl_rotate_y(float64 angle);
void sl_rotate_z(float64 angle);
void sl_rotate_x(float32 angle);
void sl_rotate_y(float32 angle);
void sl_rotate_z(float32 angle);
void sl_translatef(float32 x, float32 y, float32 z);
void sl_putpixel(SLTexture *target,int32 x,int32 y, pixel32 colour);
pixel32 sl_getpixel(SLTexture *target,int32 x,int32 y);

void sl_enable_multisampling();
void sl_disable_multisampling();
void sl_disable_arrays();
void sl_enable_arrays();
void sl_cull_back();
void sl_cull_front();
void sl_disable_cull_face();
void sl_enable_cull_face();
void sl_front_cw();
void sl_front_ccw();
void sl_matrix_projection();
void sl_matrix_modelview();
void sl_load_identity();
void sl_enable_texturing();
void sl_disable_texturing();
void sl_enable_texture_filtering();
void sl_disable_texture_filtering();

void sl_enable_blending();
void sl_blend_src_alpha_one_minus();
void sl_blend_alpha_saturate_one();
void sl_blend_one_one();
void sl_blend_src_alpha_one();
void sl_disable_blending();
void sl_enable_alpha(float_t v);
void sl_disable_alpha();
void sl_enable_depthtest();
void sl_disable_depthtest();
void sl_enable_colour_material();
void sl_disable_colour_material();
void sl_material_ambient(float_t* values);
void sl_material_diffuse(float_t* values);
void sl_material_emissive(float_t* values);
void sl_material_specular(float_t* values);
void sl_material_shininess(float_t* value);
void sl_line_width(float_t w);
void sl_point_size(float_t w);
void sl_enable_multisample();
void sl_disable_multisample();
void sl_enable_mipmapping();
void sl_disable_mipmapping();

void sl_begin_triangles(SLPrimitiveBuffer *target);
void sl_end_triangles(SLPrimitiveBuffer *target);
void sl_begin_lines(SLPrimitiveBuffer *target);
void sl_end_lines(SLPrimitiveBuffer *target);
void sl_begin_quads(SLPrimitiveBuffer *target);
void sl_end_quads(SLPrimitiveBuffer *target);

void sl_triangle(SLPrimitiveBuffer *target,
    float32 x1, float32 y1, 
    float32 x2, float32 y2, 
    float32 x3, float32 y3, pixel32 colour);
void sl_triangle(SLPrimitiveBuffer *target,
    vec3 vertex1,vec3 vertex2,vec3 vertex3,
    pixel32 colour);
void sl_triangle(SLPrimitiveBuffer *target,
    float32 x1, float32 y1, 
    float32 x2, float32 y2, 
    float32 x3, float32 y3, 
	pixel32 colour1,pixel32 colour2,pixel32 colour3);
void sl_triangle(SLPrimitiveBuffer *target,
    vec3 vertex1,vec3 vertex2,vec3 vertex3,
    ARGB3 colours);
void sl_rectangle(SLPrimitiveBuffer *target,
    float32 x,float32 y,float32 width, float32 height, pixel32 colour);

