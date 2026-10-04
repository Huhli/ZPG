#pragma once

#include <glad/gl.h>

class Shader
{
public:
    Shader(GLenum type, const char* filename);
    ~Shader();

    GLuint getId() const;

private:
    GLuint id;

    void loadFromFile(
        GLenum type,
        const char* filename
    );
};