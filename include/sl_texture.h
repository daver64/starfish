#pragma once
#include "sl.h"

class Texture {
public:
    Texture(int32 width,int32 height,bool mipmapped);
    ~Texture();

    int32 width;
    int32 height;
    bool mipmapped;
    uint32 glref;
    pixel32 *pixeldata;
};

 