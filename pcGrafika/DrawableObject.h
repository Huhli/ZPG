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

    void setTransformation(CompositeTransformation* transformation);

private:
    Transformation transformation;
    CompositeTransformation* assignedTransformation = nullptr;

    Model* model;
    ShaderProgram* shaderProgram;
};