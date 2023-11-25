#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "sl_context.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

//#define GLFW_INCLUDE_GLEXT
#include <GLFW/glfw3.h>
//#include <sl_glext.h>
#include <AL/al.h>
#include <AL/alc.h>

#include <cstdlib>
#include <cstdio>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

static void glfw_error_callback(int error, const char *description)
{
    fprintf(stderr, "Error %d : %s\n", error, description);
}
static void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}
int32 sl_create_context(SLContext **context,const char *titletext, int32 width, int32 height, bool fullscreen)
{
    glfwSetErrorCallback(glfw_error_callback);
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_DECORATED, GLFW_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
    GLFWwindow *window = glfwCreateWindow(width, height, titletext, NULL, NULL);
    if (!window)
    {
        fprintf(stderr, "failed to create window\n");
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glViewport(0, 0, width, height);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSwapInterval(1);

    GLFWimage images[2];
    images[0].pixels = stbi_load("bud.png", &images[0].width, &images[0].height, 0, 4);
    images[1].pixels = stbi_load("bud.png", &images[1].width, &images[1].height, 0, 4);
    if (images[0].pixels && images[1].pixels)
    {
        glfwSetWindowIcon(window, 2, images);
        stbi_image_free(images[0].pixels);
    }
    *context = new SLContext;
    (*context)->width = width;
    (*context)->height = height;
    (*context)->fullscreen = fullscreen;
    (*context)->window = window;
    (*context)->quit_requested = false;

    sl_load_gl_extensions();
    return 0;
}
int32 sl_destroy_context(SLContext **context)
{
    assert(*context);
    delete (*context);
    *context = nullptr;
    glfwTerminate();
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
    context->quit_requested = true;
}

void sl_swap(SLContext *context)
{
    glfwSwapBuffers(context->window);
}
void sl_poll_input(SLContext *context)
{
    glfwPollEvents();
    if (glfwWindowShouldClose(context->window))
    {
        context->quit_requested = true;
    }
}

void sl_process_input(SLContext *context)
{
    if (glfwGetKey(context->window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        sl_quit(context);
        glfwSetWindowShouldClose(context->window, true);
    }
}
