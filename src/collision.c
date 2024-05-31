#include "collision.h"
#include <float.h>
#include "vector.h"

static bool checkAxis(Polygon *_left, Polygon *_right, Vector *_axis)
{
    double _leftMinimalPosition = DBL_MAX;
    double _leftMaximalPosition = DBL_MIN;
    double _rightMinimalPosition = DBL_MAX;
    double _rightMaximalPosition = DBL_MIN;

    for(int _j = 0; _j < _left->n; _j++)
    {
        double _product = dotProduct(_axis, addVectors(_left->vertex[_j], _left->position));

        if(_product < _leftMinimalPosition)
            _leftMinimalPosition = _product;

        if(_product > _leftMaximalPosition)
            _leftMaximalPosition = _product;
    }

    for(int _j = 0; _j < _right->n; _j++)
    {
        double _product = dotProduct(_axis, addVectors(_right->vertex[_j], _right->position));

        if(_product < _rightMinimalPosition)
            _rightMinimalPosition = _product;

        if(_product > _rightMaximalPosition)
            _rightMaximalPosition = _product;
    }

    if(_leftMaximalPosition < _rightMinimalPosition)
        return false;

    if(_rightMaximalPosition < _leftMinimalPosition)
        return false;

    return true;
}

bool checkCollision(Polygon *_left, Polygon *_right)
{
    for(int _i = 0; _i < _left->n; _i++)
    {
        Vector *_a = addVectors(_left->vertex[_i], _left->position);
        Vector *_b = addVectors(_left->vertex[(_i + 1) % _left->n], _left->position);
        Vector *_normal = constructVector(_a->y - _b->y, _b->x - _a->x);
        
        if(!checkAxis(_left, _right, _normal))
           return false;
    }

    for(int _i = 0; _i < _right->n; _i++)
    {
        Vector *_a = addVectors(_right->vertex[_i], _right->position);
        Vector *_b = addVectors(_right->vertex[(_i + 1) % _right->n], _right->position);
        Vector *_normal = constructVector(_a->y - _b->y, _b->x - _a->x);
        
        if(!checkAxis(_left, _right, _normal))
           return false;
    }

    return true;
}
