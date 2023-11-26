#pragma once
#include "sl.h"

class Texture {
public:
    Texture(int32 width,int32 height,bool mipmapped);
    ~Texture();
    void putpixel(int32 x,int32 y, pixel32 colour);
    pixel32 getpixel(int32 x,int32 y);
    int32 width;
    int32 height;
    bool mipmapped;
    uint32 glref;
    pixel32 *pixeldata;
};

void sl_enable_texture_filtering();
void sl_disable_texture_filtering();
