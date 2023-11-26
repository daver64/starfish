#include "sl_context.h"
#include "sl_draw.h"
#include "sl_texture.h"
#include <cassert>

void sl_clrscr(SLContext *context,pixel32 colour)
{
     glViewport(0, 0, context->width, context->height);
    float r=getr_nf(colour);
    float g=getg_nf(colour);
    float b=getb_nf(colour);
    glClearColor(r,g,b,0);
    glClear(GL_COLOR_BUFFER_BIT);
}
void putpixel(Texture *target,int32 x,int32 y, pixel32 colour)
{
    assert(x>=0 && x<target->width);
    assert(y>=0 && y<target->height);
    target->pixeldata[y*target->width+x]=colour;
}
pixel32 getpixel(Texture *target,int32 x,int32 y)
{
    assert(x>=0 && x<target->width);
    assert(y>=0 && y<target->height);
    return target->pixeldata[y*target->width+x];
}
