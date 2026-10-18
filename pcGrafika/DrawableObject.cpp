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

    const glm::mat4 modelMatrix =
        assignedTransformation != nullptr
        ? assignedTransformation->getMatrix()
        : transformation.getMatrix();

    shaderProgram->setUniform("modelMatrix", modelMatrix);

    model->draw();
}

Transformation& DrawableObject::getTransformation()
{
    return transformation;
}

void DrawableObject::setTransformation(
    CompositeTransformation* transformation
)
{
    assignedTransformation = transformation;
}