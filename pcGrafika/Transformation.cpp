#include "Transformation.h"


Transformation::Transformation()
{
    x = 0.0f;
    y = 0.0f;
    z = 0.0f;

    scale = 1.0f;

    rotationY = 0.0f;
}


void Transformation::translate(
    float x,
    float y,
    float z
)
{
    this->x += x;
    this->y += y;
    this->z += z;
}


void Transformation::scaleBy(float value)
{
    scale *= value;
}


void Transformation::rotateY(float angle)
{
    rotationY += angle;
}


float Transformation::getX() const
{
    return x;
}


float Transformation::getY() const
{
    return y;
}


float Transformation::getZ() const
{
    return z;
}


float Transformation::getScale() const
{
    return scale;
}


float Transformation::getRotationY() const
{
    return rotationY;
}