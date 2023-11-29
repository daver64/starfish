/**
 * (c) 2023 David Rowbotham thedaver64@gmail.com
 */
#include "sl.h"
#include "sl_draw.h"
#include "sl_framebuffer.h"
#include "sl_primitivebuffer.h"
#include "sl_texture.h"
#include "sl_context.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
SLContext *context{nullptr};
SLTexture *tex{nullptr};
SLPrimitiveBuffer *geometry{nullptr};

int main(int argc, char *argv[])
{
    int32 screen_w = 800;
    int32 screen_h = 600;
    bool fullscreen = false;
    int32 result = sl_create_context(&context, "simlib app", screen_w, screen_h, fullscreen);

    tex = new SLTexture("../src/bud.png", false);
    geometry = new SLPrimitiveBuffer;

    sl_disable_depthtest();

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    ImGui::StyleColorsDark();

    const char *glsl_version = "#version 130";
    ImGui_ImplGlfw_InitForOpenGL(context->window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    do
    {
        sl_process_input(context);
        sl_ortho(context);
        sl_clrscr(context);


        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        bool is_open=true;
        ImGui::SetNextWindowPos(ImVec2(0,0));
        ImGui::Begin("Name", &is_open, 
            ImGuiWindowFlags_NoTitleBar|
            ImGuiWindowFlags_Modal|
            ImGuiWindowFlags_NoMove|
            ImGuiWindowFlags_NoResize);
        ImGui::Text("textlabel");
        ImGui::End();
        ImGui::Render();

        // test drawing.
        sl_disable_texturing();
        sl_begin_triangles(geometry);
        sl_triangle(geometry, 10, 100, 100, 10, 200, 100, x11colours::red, x11colours::green, x11colours::blue);
        sl_end_triangles(geometry);

        sl_enable_texturing();
        sl_bind_texture(geometry, tex);
        sl_begin_quads(geometry);
        sl_rectangle(geometry, 512, 200, 128, 128, x11colours::white);
        sl_end_quads(geometry);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        // main_graphics(context);
        sl_swap(context);
        sl_poll_input(context);

    } while (!sl_want_to_quit(context));

    sl_destroy_context(&context);
    delete tex;
    delete geometry;

    return 0;
}