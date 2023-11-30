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

ImGuiIO io;


void init_gui(SLContext *context)
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    ImGui::StyleColorsDark();

    const char *glsl_version = "#version 130";
    ImGui_ImplGlfw_InitForOpenGL(context->window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);
}

void update_gui()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    bool is_open = true;
    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::Begin("Name", &is_open,
                 ImGuiWindowFlags_NoTitleBar |
                     ImGuiWindowFlags_Modal |
                     ImGuiWindowFlags_NoMove |
                     ImGuiWindowFlags_NoResize);
    ImGui::Text("textlabel");
    ImGui::End();
    ImGui::Render();
}

void render_gui()
{
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}