#include <stdlib.h>
#include <GLFW/glfw3.h>
#include "renderer.h"
#include "polygon.h"

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
    Vector *_position = constructVector(0.0, 0.0);

    Polygon *_polygon = (Polygon *)constructPolygon(_vertex, _n, _position, 0.25f);

    changePolygonsAngularAcceleration(_polygon, -1.0f);

    float _deltaTime = 0.0f;

    setDrawColor(0.0f, 0.75f, 0.25f);

    while(isOpen())
    {
        float _start = glfwGetTime();

        clearRenderer();

        updatePolygon(_polygon, _deltaTime);

        renderLinePolygon(_polygon);

        updateRenderer();

        float _stop = glfwGetTime();
        _deltaTime = _stop-_start;
    }

    closeRenderer();
    return 0;
}
