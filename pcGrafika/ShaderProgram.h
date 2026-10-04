#pragma once

#include <glad/gl.h>

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

    GLuint getId() const;

private:
    GLuint id;
};