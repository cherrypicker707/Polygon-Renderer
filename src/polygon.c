#include "polygon.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "vector.h"

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
    Vector **_vertex = _polygon->vertex;
    Vector *_position = _polygon->position;
    unsigned int _vao = _polygon->vao;
    unsigned int _vbo = _polygon->vbo;

    double *_vertexData = (double *)malloc(2 * _n * sizeof(double));

    for(int _i = 0; _i < _n; _i++)
    {
        _vertexData[2 * _i] = _position->x + _vertex[_i]->x;
        _vertexData[2 * _i + 1] = _position->y + _vertex[_i]->y;
    }

    glBindVertexArray(_vao);

    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glBufferData(GL_ARRAY_BUFFER, 2 * _n * sizeof(double), _vertexData, GL_DYNAMIC_DRAW);

    glVertexAttribPointer(0, 2, GL_DOUBLE, GL_FALSE, 2 * sizeof(double), (void *)0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

Polygon *constructPolygon(Vector **_vertex, unsigned int _n, Vector *_position, double _scale)
{
    Polygon *_polygon = (Polygon *)malloc(sizeof(Polygon));

    _polygon->n = _n;
    _polygon->vertex = (Vector **)malloc(_n * sizeof(Vector *));
    for(int _i = 0; _i < _n; _i++)
    {
        _polygon->vertex[_i] = (Vector *)malloc(sizeof(Vector));
        _polygon->vertex[_i]->x = _scale * _vertex[_i]->x;
        _polygon->vertex[_i]->y = _scale * _vertex[_i]->y;
    }
    _polygon->position = (Vector *)malloc(sizeof(Vector));
    _polygon->position->x = _position->x;
    _polygon->position->y = _position->y;
    _polygon->velocity = (Vector *)malloc(sizeof(Vector));
    _polygon->velocity->x = 0.0;
    _polygon->velocity->y = 0.0;
    _polygon->acceleration = (Vector *)malloc(sizeof(Vector));
    _polygon->acceleration->x = 0.0;
    _polygon->acceleration->y = 0.0;
    _polygon->angularVelocity = 0.0;
    _polygon->angularAcceleration = 0.0;

    glGenVertexArrays(1, &_polygon->vao);
    glGenBuffers(1, &_polygon->vbo);
    glGenBuffers(1, &_polygon->ebo);

    updateEBO(_polygon);
    updateVBO(_polygon);

    return _polygon;
}

void setPolygonsPosition(Polygon *_polygon, Vector *_position)
{
    _polygon->position->x = _position->x;
    _polygon->position->y = _position->y;
}

void changePolygonsPosition(Polygon *_polygon, Vector *_displacement)
{
    _polygon->position->x += _displacement->x;
    _polygon->position->y += _displacement->y;
}

void setPolygonsVelocity(Polygon *_polygon, Vector *_velocity)
{
    _polygon->velocity->x = _velocity->x;
    _polygon->velocity->y = _velocity->y;
}

void changePolygonsVelocity(Polygon *_polygon, Vector *_changeInVelocity)
{
    _polygon->velocity->x += _changeInVelocity->x;
    _polygon->velocity->y += _changeInVelocity->y;
}

void setPolygonsAcceleration(Polygon *_polygon, Vector *_acceleration)
{
    _polygon->acceleration->x = _acceleration->x;
    _polygon->acceleration->y = _acceleration->y;
}

void changePolygonsAcceleration(Polygon *_polygon, Vector *_changeInAcceleration)
{
    _polygon->acceleration->x += _changeInAcceleration->x;
    _polygon->acceleration->y += _changeInAcceleration->y;
}

void rotatePolygon(Polygon *_polygon, double _angle)
{
    int _n = _polygon->n;
    Vector **_vertex = _polygon->vertex;

    for(int _i = 0; _i < _n; _i++)
    {
        float _x = _vertex[_i]->x;
        float _y = _vertex[_i]->y;

        _vertex[_i]->x = _x * cos(_angle) - _y * sin(_angle);
        _vertex[_i]->y = _x * sin(_angle) + _y * cos(_angle);
    }
}

void setPolygonsAngularVelocity(Polygon *_polygon, double _angularVelocity)
{
    _polygon->angularVelocity = _angularVelocity;
}

void changePolygonsAngularVelocity(Polygon *_polygon, double _changeInAngularVelocity)
{
    _polygon->angularVelocity += _changeInAngularVelocity;
}

void setPolygonsAngularAcceleration(Polygon *_polygon, double _angularAcceleration)
{
    _polygon->angularAcceleration = _angularAcceleration;
}

void changePolygonsAngularAcceleration(Polygon *_polygon, double _changeInAngularAcceleration)
{
    _polygon->angularAcceleration += _changeInAngularAcceleration;
}

void updatePolygon(Polygon *_polygon, double _changeInTime)
{
    Vector *_acceleration = _polygon->acceleration;
    double _angularAcceleration = _polygon->angularAcceleration;

    _polygon->velocity->x += _changeInTime * _acceleration->x;
    _polygon->velocity->y += _changeInTime * _acceleration->y;
    _polygon->angularVelocity += _changeInTime * _angularAcceleration;

    Vector *_velocity = _polygon->velocity;
    double _angularVelocity = _polygon->angularVelocity;

    changePolygonsPosition(_polygon, constructVector(_changeInTime * _velocity->x, _changeInTime * _velocity->y));
    rotatePolygon(_polygon, _changeInTime * _angularVelocity);

    updateVBO(_polygon);
}

void renderLinePolygon(Polygon *_polygon)
{
    glBindVertexArray(_polygon->vao);
    glDrawElements(GL_LINES, 2*_polygon->n, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}
