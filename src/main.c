#include <stdlib.h>
#include <GLFW/glfw3.h>
#include "renderer.h"
#include "polygon.h"

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

int main()
{
    loadRenderer(WINDOW_WIDTH, WINDOW_HEIGHT, "Polygon-Renderer");

    float _vertex[] = {
        -0.5f, -0.5f,
        -0.5f, 0.5f,
        0.5f, 0.5f,
        0.5f, -0.5f
    };
    int _n = 4;

    Polygon *_polygon = (Polygon *)createPolygon(_vertex, _n, 0.0f, 0.0f, 0.25f);

    changePolygonRotationalAcceleration(_polygon, -1.0f);

    float _deltaTime = 0.0f;

    setDrawColor(0.0f, 0.75f, 0.25f);

    while(isOpen())
    {
        float _start = glfwGetTime();

        clearRenderer();

        updatePolygon(_polygon, _deltaTime);

        renderPolygon(_polygon);

        updateRenderer();

        float _stop = glfwGetTime();
        _deltaTime = _stop-_start;
    }

    closeRenderer();
    return 0;
}
