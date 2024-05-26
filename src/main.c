#include <stdlib.h>
#include "renderer.h"
#include "polygon.h"

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

float *parseCoordinates(float *_windowCoordinates, int _n)
{
    float *_normalizedCoordinates = (float *)malloc(2*_n*sizeof(float));

    for(int _i = 0; _i < _n; _i++)
    {
        _normalizedCoordinates[2*_i] = (_windowCoordinates[2*_i]/WINDOW_WIDTH)*2.0f-1.0f;
        _normalizedCoordinates[2*_i+1] = 1.0f-(_windowCoordinates[2*_i+1]/WINDOW_HEIGHT)*2.0f;
    }

    return _normalizedCoordinates;
}

int main()
{
    loadRenderer(WINDOW_WIDTH, WINDOW_HEIGHT, "Polygon-Renderer");

    float _vertex[] = {
        10.0f, 10.0f,
        300.0f, 15.0f,
        30.0f, 25.0f,
        20.0f, 25.0f,
        15.0f, 20.0f
    };
    int _n = 5;

    Polygon *_polygon = (Polygon *)createPolygon(parseCoordinates(_vertex, _n), _n);

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
