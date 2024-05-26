#ifndef POLYGON
#define POLYGON

typedef struct {
    int n;
    float x, y;
    unsigned int vao, vbo, ebo;
} Polygon;

Polygon *createPolygon(float *_vertexPosition, int _n);
void renderPolygon(Polygon *_polygon);

#endif
