
#pragma once

#include <glm/glm.hpp>

class Camera
{
public:
    Camera();

    glm::mat4 getViewMatrix() const;
    glm::mat4 getProjectionMatrix(float aspect) const;
    glm::vec3 getPosition() const;

    void moveForward(float distance);
    void moveRight(float distance);
    void rotate(float deltaX, float deltaY);

private:
    glm::vec3 eye;
    glm::vec3 target;
    glm::vec3 up;

    float alpha;
    float fi;

    void updateTarget();
};
