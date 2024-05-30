#include "vector.h"
#include <stdlib.h>

Vector *constructVector(double _x, double _y)
{
    Vector *_vector = (Vector *)malloc(sizeof(Vector));

    _vector->x = _x;
    _vector->y = _y;

    return _vector;
}

Vector *addVectors(Vector *_left, Vector *_right)
{
    return constructVector(_left->x + _right->x, _left->y + _right->y);
}

Vector *multiplyVector(Vector *_vector, double _scalar)
{
    return constructVector(_scalar * _vector->x, _scalar * _vector->y);
}

double dotProduct(Vector *_left, Vector *_right)
{
    return (_left->x * _right->x) + (_left->y * _right->y);
}
