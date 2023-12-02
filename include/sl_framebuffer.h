/**
 * (c) 2023 David Rowbotham thedaver64@gmail.com
*/
#pragma once
#include "sl.h"


class SLFrameBuffer {
public:
    void bind();
    void unbind();
    void resize(int32 w,int32 h);
    void ortho2d();
    void clear();

    int32 glref;
    int32 width;
    int32 height;
};