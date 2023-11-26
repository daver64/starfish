
#include "sl.h"
#include "sl_draw.h"
#include "sl_framebuffer.h"
#include "sl_primitivebuffer.h"
#include "sl_texture.h"

SLContext *context{nullptr};
SLTexture *tex{nullptr};
SLPrimitiveBuffer *geometry{nullptr};


int main(int argc, char *argv[])
{       
    int32 screen_w=800;
    int32 screen_h=600;
    bool fullscreen=false;
    int32 result=sl_create_context(&context,"simlib app",screen_w,screen_h,fullscreen);
    
    tex=new SLTexture(256,256,true);
    geometry=new SLPrimitiveBuffer;

    sl_disable_depthtest();
    sl_disable_texturing();

    do {
        sl_process_input(context);
        sl_ortho(context);
        sl_clrscr(context);
        sl_trianglefill(geometry,10,100,100,10,200,100,x11colours::silver);
        sl_swap(context);
        sl_poll_input(context);
    } while(!sl_want_to_quit(context));

    sl_destroy_context(&context);   
    delete tex;
    delete geometry;

    return 0;
}