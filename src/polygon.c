#include "polygon.h"
#include <stdlib.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

Polygon *createPolygon(float *_vertexPosition, int _n)
{
    Polygon *_polygon = (Polygon *)malloc(sizeof(Polygon));

    _polygon->n = _n;
    _polygon->x = 0.0f;
    _polygon->y = 0.0f;

    unsigned int *_vertexOrder = (unsigned int *)malloc(3*(_n-2)*sizeof(unsigned int));
    for(int _i = 0; _i < _n-2; _i++)
    {
        _vertexOrder[3*_i] = 0;
        _vertexOrder[3*_i+1] = _i+1;
        _vertexOrder[3*_i+2] = _i+2;
    }

    glGenVertexArrays(1, &_polygon->vao);
    glGenBuffers(1, &_polygon->vbo);
    glGenBuffers(1, &_polygon->ebo);

    glBindVertexArray(_polygon->vao);

    glBindBuffer(GL_ARRAY_BUFFER, _polygon->vbo);
    glBufferData(GL_ARRAY_BUFFER, 2*_n*sizeof(float), _vertexPosition, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _polygon->ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 3*(_n-2)*sizeof(unsigned int), _vertexOrder, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2*sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    
    return _polygon;
}

void renderPolygon(Polygon *_polygon)
{
    glBindVertexArray(_polygon->vao);
    glDrawElements(GL_TRIANGLES, 3*(_polygon->n-2), GL_UNSIGNED_INT, 0);
}
