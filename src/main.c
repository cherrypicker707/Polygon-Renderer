#include "renderer.h"
#include "polygon.h"

int main()
{
    loadRenderer(1280, 720, "Polygon-Renderer");

    float _vertices[] = {
        -0.5f, -0.5f,
        0.0f, 0.5f,
        0.5f, -0.5f
    };
    Polygon *_polygon = (Polygon *)createPolygon(_vertices, 3);

    setDrawColor(0.0f, 0.75f, 0.25f);

    while(isOpen())
    {
        clearRenderer();

        renderPolygon(_polygon);

        updateRenderer();
    }

    closeRenderer();
    return 0;
}
