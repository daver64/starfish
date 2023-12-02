/**
 * (c) 2023 David Rowbotham thedaver64@gmail.com
 */
#pragma once
#include "sl.h"

class SLTexture
{
public:
    SLTexture(int32 width, int32 height, bool clamped, bool mipmapped);
    SLTexture(const char *filename, bool clamped, bool mipmapped);
    ~SLTexture();

    int32 width;
    int32 height;
    bool mipmapped;
    uint32 glref;
    pixel32 *pixeldata;
};

class SLTextureAtlas
{
public:
    SLTextureAtlas(SLPrimitiveBuffer *target,const char *filename, int32 numtiles_x, int32 numtiles_y, bool clamped, bool mipmapped);
    ~SLTextureAtlas();
    void bind();
    void draw_tile(float_t x1, float_t y1, float_t width, float_t height, int32_t index, pixel32 colour = x11colours::white);
    void draw_tile(int32 x1, int32_t y1, int32_t width, int32_t height, int32_t index, pixel32 colour = x11colours::white);
    void batch_begin();
    void batch_draw_tile(float_t x1, float_t y1, float_t width, float_t height, int32 index, pixel32 colour = x11colours::white);
    void batch_draw_tile(int32 x1, int32 y1, int32 width, int32 height, int32 index, pixel32 colour = x11colours::white);
    void batch_end();
    SLTexture *texture;
    SLPrimitiveBuffer *target;
    int32 tile_width;
    int32 tile_height;
    int32 numtiles_x;
    int32 numtiles_y;
    int32 valid;
    int32 clamped;
    int32 mipmapped;
};