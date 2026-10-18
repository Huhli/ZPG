
#include "Transformation.h"

#include <glm/gtc/matrix_transform.hpp>

Transformation::Transformation()
    : matrix(1.0f)
{
}

void Transformation::translate(float x, float y, float z)
{
    matrix = glm::translate(
        glm::mat4(1.0f),
        glm::vec3(x, y, z)
    ) * matrix;
}

void Transformation::scaleBy(float value)
{
    matrix = glm::scale(
        glm::mat4(1.0f),
        glm::vec3(value, value, value)
    ) * matrix;
}

void Transformation::rotateY(float angle)
{
    matrix = glm::rotate(
        glm::mat4(1.0f),
        angle,
        glm::vec3(0.0f, 1.0f, 0.0f)
    ) * matrix;
}

void Transformation::rotateZ(float angle)
{
    matrix = glm::rotate(
        glm::mat4(1.0f),
        angle,
        glm::vec3(0.0f, 0.0f, 1.0f)
    ) * matrix;
}

glm::mat4 Transformation::getMatrix() const
{
    return matrix;
}

CompositeTransformation::CompositeTransformation()
{
}

void CompositeTransformation::add(TransformationComponent* transformation)
{
    if (transformation != nullptr)
    {
        transformations.push_back(transformation);
    }
}

void CompositeTransformation::clear()
{
    transformations.clear();
}

glm::mat4 CompositeTransformation::getMatrix() const
{
    glm::mat4 result(1.0f);

    for (const auto* transformation : transformations)
    {
        result = transformation->getMatrix() * result;
    }

    return result;
}