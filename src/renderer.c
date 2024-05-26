#include "renderer.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define VERTEX_SHADER_PATH "../res/vertexShader.glsl"
#define FRAGMENT_SHADER_PATH "../res/fragmentShader.glsl"

static int windowWidth;
static int windowHeight;
static GLFWwindow *window;
static unsigned int program;

static void framebufferSizeCallback(GLFWwindow *_window, int _width, int _height)
{
    windowWidth = _width;
    windowHeight = _height;
    glViewport(0, 0, windowWidth, windowHeight);
}

static const char *getFileContent(const char *_path)
{
    FILE *_file = fopen(_path, "r");
    assert(_file);

    fseek(_file, 0, SEEK_END);
    int _length = ftell(_file);
    fseek(_file, 0, SEEK_SET);

    char *_content = (char *)malloc((_length+1)*sizeof(char));
    fread(_content, sizeof(char), _length, _file);

    fclose(_file);

    _content[_length] = '\0';

    return _content;
}

static unsigned int loadVertexShader()
{
    const char *_shaderSource = getFileContent(VERTEX_SHADER_PATH);
    unsigned int _shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(_shader, 1, &_shaderSource, NULL);
    glCompileShader(_shader);

    int _status;
    glGetShaderiv(_shader, GL_COMPILE_STATUS, &_status);
    assert(_status);

    return _shader;
}

static unsigned int loadFragmentShader()
{
    const char *_shaderSource = getFileContent(FRAGMENT_SHADER_PATH);
    unsigned int _shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(_shader, 1, &_shaderSource, NULL);
    glCompileShader(_shader);

    int _status;
    glGetShaderiv(_shader, GL_COMPILE_STATUS, &_status);
    assert(_status);

    return _shader;
}

static unsigned int loadProgram()
{
    unsigned int _vertexShader = loadVertexShader();
    unsigned int _fragmentShader = loadFragmentShader();

    unsigned int _program = glCreateProgram();
    glAttachShader(_program, _vertexShader);
    glAttachShader(_program, _fragmentShader);
    glLinkProgram(_program);

    int status;
    glGetProgramiv(_program, GL_LINK_STATUS, &status);
    assert(status);

    glDeleteShader(_vertexShader);
    glDeleteShader(_fragmentShader);

    return _program;
}

void loadRenderer(int _windowWidth, int _windowHeight, const char *_windowTitle)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    windowWidth = _windowWidth;
    windowHeight = _windowHeight;
    window = glfwCreateWindow(windowWidth, windowHeight, _windowTitle, NULL, NULL);
    assert(window != NULL);
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);

    assert(gladLoadGLLoader((GLADloadproc)glfwGetProcAddress));
    glViewport(0, 0, windowWidth, windowHeight);

    loadProgram();
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
