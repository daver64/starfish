/**
 * (c) 2023 David Rowbotham thedaver64@gmail.com
*/
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

