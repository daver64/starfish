
#include "starfish.h"
#include "sl.h"
#include "sl_draw.h"
#include "sl_framebuffer.h"
#include "sl_primitivebuffer.h"
#include "sl_texture.h"

SLContext *context{nullptr};
int main(int argc, char *argv[])
{
    int32 result=sl_create_context(&context,800,600,false);
    
    do {
        sl_process_input(context);
        sl_clrscr(context,rgb(100,0,0));
        sl_swap(context);
        sl_poll_input(context);
    } while(!sl_want_to_quit(context));

    sl_destroy_context(&context);
    return 0;
}