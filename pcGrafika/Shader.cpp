#include "Shader.h"

#include <iostream>
#include <fstream>
#include <string>
#include <iterator>
#include <cstdlib>


Shader::Shader(GLenum type, const char* filename)
{
    loadFromFile(type, filename);
}


Shader::~Shader()
{
    if (id != 0)
    {
        glDeleteShader(id);
    }
}


void Shader::loadFromFile(
    GLenum type,
    const char* filename
)
{
    id = glCreateShader(type);

    if (id == 0)
    {
        std::cout << "Unable to create shader!" << std::endl;
        exit(EXIT_FAILURE);
    }


    std::ifstream file(filename);

    if (!file.is_open())
    {
        std::cout << "Unable to open shader file: "
            << filename
            << std::endl;

        glDeleteShader(id);
        id = 0;

        exit(EXIT_FAILURE);
    }


    std::string shaderCode(
        (std::istreambuf_iterator<char>(file)),
        std::istreambuf_iterator<char>()
    );


    const char* source = shaderCode.c_str();


    glShaderSource(
        id,
        1,
        &source,
        nullptr
    );


    glCompileShader(id);


    GLint success;

    glGetShaderiv(
        id,
        GL_COMPILE_STATUS,
        &success
    );


    if (!success)
    {
        char infoLog[1024];

        glGetShaderInfoLog(
            id,
            sizeof(infoLog),
            nullptr,
            infoLog
        );

        std::cout
            << "Shader compilation failed:\n"
            << infoLog
            << std::endl;

        glDeleteShader(id);
        id = 0;

        exit(EXIT_FAILURE);
    }
}


GLuint Shader::getId() const
{
    return id;
}