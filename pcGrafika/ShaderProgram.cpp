#include "ShaderProgram.h"

#include <iostream>
#include <cstdlib>


ShaderProgram::ShaderProgram(
    const char* vertexShaderFile,
    const char* fragmentShaderFile
)
{
    Shader vertexShader(
        GL_VERTEX_SHADER,
        vertexShaderFile
    );

    Shader fragmentShader(
        GL_FRAGMENT_SHADER,
        fragmentShaderFile
    );


    id = glCreateProgram();


    glAttachShader(
        id,
        vertexShader.getId()
    );

    glAttachShader(
        id,
        fragmentShader.getId()
    );


    glLinkProgram(id);


    GLint success;

    glGetProgramiv(
        id,
        GL_LINK_STATUS,
        &success
    );


    if (!success)
    {
        char infoLog[1024];

        glGetProgramInfoLog(
            id,
            sizeof(infoLog),
            nullptr,
            infoLog
        );

        std::cout
            << "Shader program linking failed:\n"
            << infoLog
            << std::endl;

        glDeleteProgram(id);

        id = 0;

        exit(EXIT_FAILURE);
    }
}


ShaderProgram::~ShaderProgram()
{
    if (id != 0)
    {
        glDeleteProgram(id);
    }
}


void ShaderProgram::use()
{
    glUseProgram(id);
}

void ShaderProgram::setUniform(
    const char* name,
    float value
)
{
    GLint location =
        glGetUniformLocation(id, name);

    if (location == -1)
    {
        std::cout
            << "Uniform variable not found: "
            << name
            << std::endl;

        return;
    }

    glUniform1f(
        location,
        value
    );
}


void ShaderProgram::setUniform(
    const char* name,
    float x,
    float y,
    float z
)
{
    GLint location =
        glGetUniformLocation(id, name);

    if (location == -1)
    {
        std::cout
            << "Uniform variable not found: "
            << name
            << std::endl;

        return;
    }

    glUniform3f(
        location,
        x,
        y,
        z
    );
}


GLuint ShaderProgram::getId() const
{
    return id;
}