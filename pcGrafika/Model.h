#pragma once

#include <glad/gl.h>

class Model
{
public:
    Model(
        const float* vertices,
        int size,
        int vertexCount,
        bool hasNormal
    );

    ~Model();

    void draw();

    GLuint getVao() const;

private:
    GLuint vao;
    GLuint vbo;

    int vertexCount;
};