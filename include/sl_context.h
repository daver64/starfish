/**
 * (c) 2023 David Rowbotham thedaver64@gmail.com
*/
#pragma once
#include <GLFW/glfw3.h>
#include <atomic>
#include "sl.h"

struct SLContext {
    std::atomic<bool> quit_requested;
    int32 width;
    int32 height;
    bool fullscreen;
    GLFWwindow *window;
};
