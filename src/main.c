#include "renderer.h"
#include "polygon.h"

int main()
{
    loadRenderer(1280, 720, "Polygon-Renderer");

    while(isOpen())
    {
        clearRenderer();
        updateRenderer();
    }

    closeRenderer();
    return 0;
}
