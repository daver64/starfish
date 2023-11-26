
#include "sl.h"
#include "sl_draw.h"
#include "sl_framebuffer.h"
#include "sl_primitivebuffer.h"
#include "sl_texture.h"

SLContext *context{nullptr};
SLTexture *tex{nullptr};
SLPrimitiveBuffer *geometry{nullptr};

void sl_trianglefill(SLPrimitiveBuffer *target,
    float32 x1, float32 y1, 
    float32 x2, float32 y2, 
    float32 x3, float32 y3, pixel32 colour)
{
	//GLPrimitiveBuffer* pbuf = gl_get_immediate();
	target->colour(colour);
	target->begin(GL_TRIANGLES);
	target->vertex(vec2(x1, y1));
	target->vertex(vec2(x2, y2));
	target->vertex(vec2(x3, y3));
	target->end();
}

int main(int argc, char *argv[])
{       
    int32 screen_w=800;
    int32 screen_h=600;
    bool fullscreen=false;
    int32 result=sl_create_context(&context,"simlib app",screen_w,screen_h,fullscreen);
    
    tex=new SLTexture(256,256,true);

    geometry=new SLPrimitiveBuffer(GL_TRIANGLES,GL_DYNAMIC_DRAW);
    sl_disable_depthtest();
    sl_disable_texturing();
    do {
        sl_process_input(context);
        sl_ortho(context);
        sl_clrscr(context,rgb(100,0,0));
        sl_trianglefill(geometry,10,100,100,10,200,100,argb(200,200,0,255));
        sl_swap(context);
        sl_poll_input(context);
    } while(!sl_want_to_quit(context));
    delete tex;
    sl_destroy_context(&context);
    return 0;
}