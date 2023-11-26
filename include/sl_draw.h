/**
 * (c) 2023 David Rowbotham thedaver64@gmail.com
*/
#pragma once
#include "sl.h"

void sl_clrscr(SLContext *context,pixel32 colour);
void putpixel(Texture *target,int32 x,int32 y, pixel32 colour);
pixel32 getpixel(Texture *target,int32 x,int32 y);