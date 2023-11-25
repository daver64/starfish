#include "sl_context.h"
#include "sl_draw.h"

void sl_clrscr(SLContext *context,pixel32 colour)
{
     glViewport(0, 0, context->width, context->height);
    float r=getr_nf(colour);
    float g=getg_nf(colour);
    float b=getb_nf(colour);
    glClearColor(r,g,b,0);
    glClear(GL_COLOR_BUFFER_BIT);
}