
/**
 * 
 * Cross Platform OpenGL Boilerplate Project
 * 
*/
#include <GLFW/glfw3.h>
#include <cstdlib>
#include <cstdio>
#include "starfish.h"

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0,0,width,height);
}
void process_input(GLFWwindow *window)
{
    if(glfwGetKey(window,GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window,true);
    }
}


int main(int argc, char *argv[])
{
    int32 result = EXIT_SUCCESS;
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,0);
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(800,600,"Starfish",NULL,NULL);
    if(!window) 
    {
        fprintf(stderr,"failed to create window\n");
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    glViewport(0,0,800,600);
    glfwSetFramebufferSizeCallback(window,framebuffer_size_callback);

    while(!glfwWindowShouldClose(window))
    {
        process_input(window);

        glClearColor(0.8f,0.8f,0.1f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return result;
}