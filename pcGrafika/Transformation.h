#pragma once

#pragma once

class Transformation
{
public:
    Transformation();

    void translate(float x, float y, float z);
    void scaleBy(float value);
    void rotateY(float angle);

    float getX() const;
    float getY() const;
    float getZ() const;

    float getScale() const;
    float getRotationY() const;

private:
    float x;
    float y;
    float z;

    float scale;
    float rotationY;
};