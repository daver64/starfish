/**
 * (c) 2023 David Rowbotham thedaver64@gmail.com
*/
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
    
    tex=new SLTexture("../src/bud.png",false);
    geometry=new SLPrimitiveBuffer;

    sl_disable_depthtest();
   

    do {
        sl_process_input(context);
        sl_ortho(context);
        sl_clrscr(context);

        // test drawing.
        sl_disable_texturing();
        sl_begin_triangles(geometry);
        sl_triangle(geometry,10,100,100,10,200,100,x11colours::red,x11colours::green,x11colours::blue);
        sl_end_triangles(geometry);

        sl_enable_texturing();
        sl_bind_texture(geometry,tex);
        sl_begin_quads(geometry);
        sl_rectangle(geometry,512,200,128,128,x11colours::white);
        sl_end_quads(geometry);

        sl_swap(context);
        sl_poll_input(context);

    } while(!sl_want_to_quit(context));

    sl_destroy_context(&context);   
    delete tex;
    delete geometry;

    return 0;
}