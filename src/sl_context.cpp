#include <GLFW/glfw3.h>
#include "sl.h"


#include <atomic>
#include <cassert>

struct SLContext {
    std::atomic<bool> quit_requested;
    int32 width;
    int32 height;
    bool fullscreen;
};


int32 sl_create_context(SLContext **context,int32 width,int32 height,bool fullscreen)
{
    assert(*context);
    *context = new SLContext;
    (*context)->width=width;
    (*context)->height=height;
    (*context)->fullscreen=fullscreen;
    return 0;
}
int32 sl_destroy_context(SLContext **context)
{
    assert(*context);
    delete (*context);
    *context=nullptr;
    return 0;
}

bool sl_want_to_quit(SLContext *context)
{
    assert(context);
    return context->quit_requested;
}
 
void sl_quit(SLContext *context)
{
    assert(context);
    context->quit_requested=true;
}
