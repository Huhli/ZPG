#pragma once

#include "Transformation.h"
#include "Model.h"
#include "ShaderProgram.h"

class DrawableObject
{
public:
    DrawableObject(
        Model* model,
        ShaderProgram* shaderProgram
    );

    void draw();

    Transformation& getTransformation();

private:
    Transformation transformation;

    Model* model;

    ShaderProgram* shaderProgram;
};