#include "DrawableObject.h"


DrawableObject::DrawableObject(
    Model* model,
    ShaderProgram* shaderProgram
)
{
    this->model = model;
    this->shaderProgram = shaderProgram;
}


void DrawableObject::draw()
{
    shaderProgram->use();

    shaderProgram->setUniform(
        "translation",
        transformation.getX(),
        transformation.getY(),
        transformation.getZ()
    );

    shaderProgram->setUniform(
        "scale",
        transformation.getScale()
    );

    shaderProgram->setUniform(
        "rotationY",
        transformation.getRotationY()
    );

    model->draw();
}

Transformation& DrawableObject::getTransformation()
{
    return transformation;
}