#include "polygon.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

static void updateEBO(Polygon *_polygon)
{
    int _n = _polygon->n;
    unsigned int _vao = _polygon->vao;
    unsigned int _ebo = _polygon->ebo;

    unsigned int *_vertexOrder = (unsigned int *)malloc(2*_n*sizeof(unsigned int));
    for(int _i = 0; _i < _n; _i++)
    {
        _vertexOrder[2*_i] = _i;
        _vertexOrder[2*_i+1] = (_i+1)%_n;
    }

    glBindVertexArray(_vao);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 2*_n*sizeof(unsigned int), _vertexOrder, GL_STATIC_DRAW);

    glBindVertexArray(0);
}

static void updateVBO(Polygon *_polygon)
{
    int _n = _polygon->n;
    float _x = _polygon->x;
    float _y = _polygon->y;
    float *_vertex = _polygon->vertex;
    unsigned int _vao = _polygon->vao;
    unsigned int _vbo = _polygon->vbo;

    for(int _i = 0; _i < _n; _i++)
    {
        _vertex[2*_i] += _x;
        _vertex[2*_i+1] += _y;
    }

    glBindVertexArray(_vao);

    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glBufferData(GL_ARRAY_BUFFER, 2*_n*sizeof(float), _vertex, GL_DYNAMIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2*sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    for(int _i = 0; _i < _n; _i++)
    {
        _vertex[2*_i] -= _x;
        _vertex[2*_i+1] -= _y;
    }
}

Polygon *createPolygon(float *_vertexPosition, int _n, float _x, float _y, float _s)
{
    Polygon *_polygon = (Polygon *)malloc(sizeof(Polygon));

    _polygon->n = _n;
    _polygon->vertex = (float *)malloc(2*_n*sizeof(float));
    for(int _i = 0; _i < _n; _i++)
    {
        _polygon->vertex[2*_i] = _s*_vertexPosition[2*_i]-_x;
        _polygon->vertex[2*_i+1] = _s*_vertexPosition[2*_i+1]-_y;
    }
    _polygon->x = _x;
    _polygon->y = _y;
    _polygon->velocityX = 0.0f;
    _polygon->velocityY = 0.0f;
    _polygon->accelerationX = 0.0f;
    _polygon->accelerationY = 0.0f;
    _polygon->rotationalVelocity = 0.0f;
    _polygon->rotationalAcceleration = 0.0f;
    glGenVertexArrays(1, &_polygon->vao);
    glGenBuffers(1, &_polygon->vbo);
    glGenBuffers(1, &_polygon->ebo);

    updateEBO(_polygon);
    updateVBO(_polygon);
    
    return _polygon;
}

void movePolygon(Polygon *_polygon, float _x, float _y)
{
    _polygon->x += _x;
    _polygon->y += _y;
    
    updateVBO(_polygon);
}

void rotatePolygon(Polygon *_polygon, float _a)
{
    int _n = _polygon->n;
    float *_vertex = _polygon->vertex;

    for(int _i = 0; _i < _n; _i++)
    {
        float _x = _vertex[2*_i];
        float _y = _vertex[2*_i+1];

        _vertex[2*_i] = _x * cos(_a) - _y * sin(_a);
        _vertex[2*_i+1] = _x * sin(_a) + _y * cos(_a);
    }

    updateVBO(_polygon);
}

void changePolygonVelocity(Polygon *_polygon, float _x, float _y)
{
    _polygon->velocityX += _x;
    _polygon->velocityY += _y;
}

void changePolygonRotationalVelocity(Polygon *_polygon, float _a)
{
    _polygon->rotationalVelocity += _a;
}

void changePolygonAcceleration(Polygon *_polygon, float _x, float _y)
{
    _polygon->accelerationX += _x;
    _polygon->accelerationY += _y;
}

void changePolygonRotationalAcceleration(Polygon *_polygon, float _a)
{
    _polygon->rotationalAcceleration += _a;
}

void updatePolygon(Polygon *_polygon, float _deltaTime)
{
    float _accelerationX = _polygon->accelerationX;
    float _accelerationY = _polygon->accelerationY;
    float _rotationalAcceleration = _polygon->rotationalAcceleration;

    _polygon->velocityX += _deltaTime * _accelerationX;
    _polygon->velocityY += _deltaTime * _accelerationY;
    _polygon->rotationalVelocity += _deltaTime * _rotationalAcceleration;

    float _velocityX = _polygon->velocityX;
    float _velocityY = _polygon->velocityY;
    float _rotationalVelocity = _polygon->rotationalVelocity;

    movePolygon(_polygon, _deltaTime * _velocityX, _deltaTime * _velocityY);
    rotatePolygon(_polygon, _deltaTime * _rotationalVelocity);
}

void renderPolygon(Polygon *_polygon)
{
    glBindVertexArray(_polygon->vao);
    glDrawElements(GL_LINES, 2*_polygon->n, GL_UNSIGNED_INT, 0);
}
