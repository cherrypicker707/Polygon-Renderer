#include <stdlib.h>
#include <GLFW/glfw3.h>
#include "renderer.h"
#include "polygon.h"
#include "collision.h"

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

int main()
{
    loadRenderer(WINDOW_WIDTH, WINDOW_HEIGHT, "Polygon-Renderer");

    int _n = 4;
    Vector **_vertex = (Vector **)malloc(4 * sizeof(Vector *));
    _vertex[0] = constructVector(-0.5, -0.5);
    _vertex[1] = constructVector(-0.5, 0.5);
    _vertex[2] = constructVector(0.5, 0.5);
    _vertex[3] = constructVector(0.5, -0.5);
    Vector *_position = constructVector(-0.5, 0.0);
    Polygon *_rectangle = (Polygon *)constructPolygon(_vertex, _n, _position, 0.25f);

    _n = 5;
    _vertex = (Vector **)malloc(5 * sizeof(Vector *));
    _vertex[0] = constructVector(-0.5, -0.5);
    _vertex[1] = constructVector(-0.5, 0.5);
    _vertex[2] = constructVector(0.0, 0.75);
    _vertex[3] = constructVector(0.5, 0.5);
    _vertex[4] = constructVector(0.5, -0.5);
    _position = constructVector(0.0, 0.5);
    Polygon *_pentagon = (Polygon *)constructPolygon(_vertex, _n, _position, 0.25);

    float _deltaTime = 0.0f;

    setDrawColor(1.0f, 1.0f, 1.0f);

    while(isOpen())
    {
        float _start = glfwGetTime();

        clearRenderer();

        updatePolygon(_rectangle, _deltaTime);
        updatePolygon(_pentagon, _deltaTime);

        setPolygonsVelocity(_pentagon, constructVector(0.0, 0.0));
        setPolygonsAngularVelocity(_pentagon, 0);
        if(getKey(GLFW_KEY_W))
            changePolygonsVelocity(_pentagon, constructVector(0.0, 0.2));
        if(getKey(GLFW_KEY_S))
            changePolygonsVelocity(_pentagon, constructVector(0.0, -0.2));
        if(getKey(GLFW_KEY_A))
            changePolygonsVelocity(_pentagon, constructVector(-0.2, 0.0));
        if(getKey(GLFW_KEY_D))
            changePolygonsVelocity(_pentagon, constructVector(0.2, 0.0));
        if(getKey(GLFW_KEY_Q))
            changePolygonsAngularVelocity(_pentagon, 0.2);
        if(getKey(GLFW_KEY_E))
            changePolygonsAngularVelocity(_pentagon, -0.2);

        setDrawColor(1.0f, 1.0f, 1.0f);
        if(checkCollision(_rectangle, _pentagon))
            setDrawColor(1.0f, 0.0f, 0.0f);

        renderLinePolygon(_rectangle);
        renderLinePolygon(_pentagon);

        updateRenderer();

        float _stop = glfwGetTime();
        _deltaTime = _stop-_start;
    }

    closeRenderer();
    return 0;
}
