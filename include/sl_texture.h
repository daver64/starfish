/**
 * (c) 2023 David Rowbotham thedaver64@gmail.com
*/
#pragma once
#include "sl.h"

class SLTexture {
public:
    SLTexture(int32 width,int32 height,bool mipmapped);
    SLTexture(const char* filename, bool mipmapped);
    ~SLTexture();

    int32 width;
    int32 height;
    bool mipmapped;
    uint32 glref;
    pixel32 *pixeldata;
};

