#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>
#include <cmath>

Camera::Camera()
{
    eye = glm::vec3(0.0f, 1.5f, 5.0f);
    up = glm::vec3(0.0f, 1.0f, 0.0f);

    alpha = glm::radians(90.0f);
    fi = glm::radians(-90.0f);

    updateTarget();
}

void Camera::updateTarget()
{
    target.x = sin(alpha) * cos(fi);
    target.z = sin(alpha) * sin(fi);
    target.y = cos(alpha);
}

glm::mat4 Camera::getViewMatrix() const
{
    return glm::lookAt(eye, eye + target, up);
}

glm::mat4 Camera::getProjectionMatrix(float aspect) const
{
    return glm::perspective(
        glm::radians(60.0f),
        aspect,
        0.1f,
        100.0f
    );
}

void Camera::moveForward(float distance)
{
    glm::vec3 direction = glm::normalize(
        glm::vec3(target.x, 0.0f, target.z)
    );

    eye += direction * distance;
}

void Camera::moveRight(float distance)
{
    glm::vec3 direction = glm::normalize(
        glm::cross(target, up)
    );

    eye += direction * distance;
}

void Camera::rotate(float deltaX, float deltaY)
{
    const float sensitivity = 0.003f;

    fi += deltaX * sensitivity;
    alpha -= deltaY * sensitivity;

    if (alpha < glm::radians(5.0f))
    {
        alpha = glm::radians(5.0f);
    }

    if (alpha > glm::radians(175.0f))
    {
        alpha = glm::radians(175.0f);
    }

    updateTarget();
}
glm::vec3 Camera::getPosition() const
{
    return eye;
}
