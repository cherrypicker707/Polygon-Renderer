#ifndef POLYGON
#define POLYGON

typedef struct {
    int n;
    float *vertex;
    float x, y;
    float velocityX, velocityY;
    float accelerationX, accelerationY;
    float rotationalVelocity;
    float rotationalAcceleration;
    unsigned int vao, vbo, ebo;
} Polygon;

Polygon *createPolygon(float *_vertexPosition, int _n, float _x, float _y, float _s);
void movePolygon(Polygon *_polygon, float _x, float _y);
void rotatePolygon(Polygon *_polygon, float _a);
void changePolygonVelocity(Polygon *_polygon, float _x, float _y);
void changePolygonRotationalVelocity(Polygon *_polygon, float _a);
void changePolygonAcceleration(Polygon *_polygon, float _x, float _y);
void changePolygonRotationalAcceleration(Polygon *_polygon, float _a);
void updatePolygon(Polygon *_polygon, float _deltaTime);
void renderPolygon(Polygon *_polygon);

#endif
