#include "renderer.h"
#include <assert.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

int windowWidth;
int windowHeight;
static GLFWwindow *window;

static void framebufferSizeCallback(GLFWwindow *_window, int _width, int _height)
{
    windowWidth = _width;
    windowHeight = _height;
    glViewport(0, 0, windowWidth, windowHeight);
}

void loadRenderer(int _windowWidth, int _windowHeight, const char *_windowTitle)
{
    glfwInit();
    glfwWindowHint(GLFW_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_VERSION_MINOR, 6);

    windowWidth = _windowWidth;
    windowHeight = _windowHeight;
    window = glfwCreateWindow(windowWidth, windowHeight, _windowTitle, NULL, NULL);
    assert(window != NULL);
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

    assert(gladLoadGLLoader((GLADloadproc)glfwGetProcAddress));
    glViewport(0, 0, windowWidth, windowHeight);
}

void updateRenderer()
{
    glfwPollEvents();
    glfwSwapBuffers(window);
}

void closeRenderer()
{
    glfwTerminate();
}

void clearRenderer()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

bool isOpen()
{
    return !glfwWindowShouldClose(window);
}