/**
 * (c) 2023 David Rowbotham thedaver64@gmail.com
*/
#pragma once
#include "sl.h"

void sl_clrscr(SLContext *context,pixel32 colour);
void sl_clrscr(SLContext *context);
void sl_clearcolour(SLContext *context,pixel32 colour);
void sl_ortho(SLContext *context, bool flip = false, float64 near_z = -1.0,float64 far_z = 1.0);
void sl_putpixel(SLTexture *target,int32 x,int32 y, pixel32 colour);
pixel32 sl_getpixel(SLTexture *target,int32 x,int32 y);

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