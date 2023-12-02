/**
 * (c) 2023 David Rowbotham thedaver64@gmail.com
 */
#include "sl.h"
#include "sl_draw.h"
#include "sl_framebuffer.h"
#include "sl_primitivebuffer.h"
#include "sl_texture.h"
#include "sl_context.h"

SLContext *context{nullptr};
SLTexture *tex{nullptr};
SLPrimitiveBuffer *geometry{nullptr};

int main(int argc, char *argv[])
{
    int32 screen_w = 800;
    int32 screen_h = 600;
    bool fullscreen = false;
    int32 result = sl_create_context(&context, "simlib app", screen_w, screen_h, fullscreen);

    tex = new SLTexture("../src/bud.png", true);
    geometry = new SLPrimitiveBuffer;

    sl_disable_depthtest();
    init_gui(context);

    do
    {
        sl_process_input(context);
        sl_ortho(context);
        sl_clrscr(context);

        update_gui();

        // test drawing.
        sl_disable_texturing();
        sl_begin_triangles(geometry);

        ARGB3 tricolours;
        vec3 v1(10.0f,100.0f,0.0f);
        vec3 v2(100.0f,10.0f,0.0f);
        vec3 v3(200.0f,100.0f,0.0f);
        sl_triangle(geometry,
                    v1,v2,v3,
                    tricolours);
        sl_end_triangles(geometry);

        sl_enable_texturing();
        sl_bind_texture(geometry, tex);
        sl_begin_quads(geometry);
        sl_rectangle(geometry, 512, 200, 128, 128, x11colours::white);
        sl_end_quads(geometry);

        render_gui();

        sl_swap(context);
        sl_poll_input(context);

    } while (!sl_want_to_quit(context));

    sl_destroy_context(&context);
    delete tex;
    delete geometry;

    return 0;
}