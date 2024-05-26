#include "renderer.h"
#include "polygon.h"

int main()
{
    loadRenderer(1280, 720, "Polygon-Renderer");

    float _vertex[] = {
        -0.5f, -0.5f,
        -0.5f, 0.5f,
        0.5f, 0.5f,
        0.5f, -0.7f,
        0.0f, -0.8f
    };
    int _size = sizeof(_vertex)/sizeof(float)/2;
    Polygon *_polygon = (Polygon *)createPolygon(_vertex, _size);

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
