#pragma once

#include <glm/glm.hpp>
#include <vector>

class TransformationComponent
{
public:
    virtual ~TransformationComponent() = default;

    virtual glm::mat4 getMatrix() const = 0;
};

class Transformation : public TransformationComponent
{
public:
    Transformation();

    void translate(float x, float y, float z);

    // Rovnomìrné škálování
    void scaleBy(float value);

    // Nerovnomìrné škálování
    void scaleBy(float x, float y, float z);

    void rotateY(float angle);
    void rotateZ(float angle);

    glm::mat4 getMatrix() const override;

private:
    glm::mat4 matrix;
};

class CompositeTransformation : public TransformationComponent
{
public:
    CompositeTransformation();

    void add(TransformationComponent* transformation);
    void clear();

    glm::mat4 getMatrix() const override;

private:
    std::vector<TransformationComponent*> transformations;
};