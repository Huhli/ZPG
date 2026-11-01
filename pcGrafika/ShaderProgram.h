
#pragma once

#include <glad/gl.h>
#include <glm/glm.hpp>

#include "Shader.h"

class ShaderProgram
{
public:
    ShaderProgram(
        const char* vertexShaderFile,
        const char* fragmentShaderFile
    );

    ~ShaderProgram();

    void use();

    void setUniform(
        const char* name,
        float value
    );

    void setUniform(
        const char* name,
        float x,
        float y,
        float z
    );

    // Set a 4x4 matrix uniform
    void setUniform(
        const char* name,
        const glm::mat4& value
    );

    GLuint getId() const;

    void setUniform(const char* name, int value);

private:
    GLuint id;
};
