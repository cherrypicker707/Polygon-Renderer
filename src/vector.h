#ifndef VECTOR
#define VECTOR

typedef struct {
    double x, y;
} Vector;

Vector *constructVector(double _x, double _y);
Vector *addVectors(Vector *_left, Vector *_right);
Vector *multiplyVector(Vector *_vector, double _scalar);
double dotProduct(Vector *_left, Vector *_right);

#endif
