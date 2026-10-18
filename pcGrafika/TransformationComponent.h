
#pragma once

#include <glm/glm.hpp>

// Common interface for individual and composite transformations
class TransformationComponent
{
public:
    virtual ~TransformationComponent() = default;

    virtual glm::mat4 getMatrix() const = 0;
};
