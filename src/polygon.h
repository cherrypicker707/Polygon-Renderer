#ifndef POLYGON
#define POLYGON

#include "vector.h"

typedef struct {
    int n;
    Vector **vertex;
    Vector *position;
    Vector *velocity;
    Vector *acceleration;
    double angularVelocity;
    double angularAcceleration;
    unsigned int vao, vbo, ebo;
} Polygon;

Polygon *constructPolygon(Vector **_vertex, unsigned int _n, Vector *_position, double _scale);
void setPolygonsPosition(Polygon *_polygon, Vector *_position);
void changePolygonsPosition(Polygon *_polygon, Vector *_displacement);
void setPolygonsVelocity(Polygon *_polygon, Vector *_velocity);
void changePolygonsVelocity(Polygon *_polygon, Vector *_changeInVelocity);
void setPolygonsAcceleration(Polygon *_polygon, Vector *_acceleration);
void changePolygonsAcceleration(Polygon *_polygon, Vector *_changeInAcceleration);
void rotatePolygon(Polygon *_polygon, double _angle);
void setPolygonsAngularVelocity(Polygon *_polygon, double _angularVelocity);
void changePolygonsAngularVelocity(Polygon *_polygon, double _changeInAngularVelocity);
void setPolygonsAngularAcceleration(Polygon *_polygon, double _angularAcceleration);
void changePolygonsAngularAcceleration(Polygon *_polygon, double _changeInAngularAccleration);
void updatePolygon(Polygon *_polygon, double _changeInTime);
void renderLinePolygon(Polygon *_polygon);

#endif
