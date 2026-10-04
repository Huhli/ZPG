#include "Model.h"


Model::Model(
    const float* vertices,
    int size,
    int vertexCount,
    bool hasNormal
)
{
    this->vertexCount = vertexCount;


    glGenBuffers(1, &vbo);

    glBindBuffer(
        GL_ARRAY_BUFFER,
        vbo
    );

    glBufferData(
        GL_ARRAY_BUFFER,
        size,
        vertices,
        GL_STATIC_DRAW
    );


    glGenVertexArrays(1, &vao);

    glBindVertexArray(vao);


    // Position
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(
        0,
        3,
        GL_FLOAT,
        GL_FALSE,
        6 * sizeof(float),
        (void*)0
    );


    // Normal / Color
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(
        1,
        3,
        GL_FLOAT,
        GL_FALSE,
        6 * sizeof(float),
        (void*)(3 * sizeof(float))
    );


    glBindBuffer(
        GL_ARRAY_BUFFER,
        0
    );

    glBindVertexArray(0);
}


Model::~Model()
{
    glDeleteVertexArrays(
        1,
        &vao
    );

    glDeleteBuffers(
        1,
        &vbo
    );
}


void Model::draw()
{
    glBindVertexArray(vao);

    glDrawArrays(
        GL_TRIANGLES,
        0,
        vertexCount
    );

    glBindVertexArray(0);
}


GLuint Model::getVao() const
{
    return vao;
}