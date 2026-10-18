
#include "Model.h"

Model::Model(
    const float* vertices,
    int size,
    int vertexCount,
    bool hasNormal,
    bool hasColor,
    bool normalBeforeColor
)
{
    this->vertexCount = vertexCount;
    this->hasColor = hasColor;

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    glBufferData(
        GL_ARRAY_BUFFER,
        size,
        vertices,
        GL_STATIC_DRAW
    );

    const int stride = (hasColor ? 9 : 6) * sizeof(float);

    // Position
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(
        0,
        3,
        GL_FLOAT,
        GL_FALSE,
        stride,
        (void*)0
    );

    if (hasColor)
    {
        // Position is already configured at location 0.

        const int colorOffset = normalBeforeColor ? 6 : 3;
        const int normalOffset = normalBeforeColor ? 3 : 6;

        // Color
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(
            1, 3, GL_FLOAT, GL_FALSE, stride,
            (void*)(colorOffset * sizeof(float))
        );

        // Normal
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(
            2, 3, GL_FLOAT, GL_FALSE, stride,
            (void*)(normalOffset * sizeof(float))
        );
    }
    else if (hasNormal)
    {
        // Normal
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(
            1,
            3,
            GL_FLOAT,
            GL_FALSE,
            stride,
            (void*)(3 * sizeof(float))
        );
    }

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

Model::~Model()
{
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
}

void Model::draw()
{
    glBindVertexArray(vao);

    GLint program = 0;
    glGetIntegerv(GL_CURRENT_PROGRAM, &program);

    GLint location = glGetUniformLocation(program, "useVertexColor");

    if (location != -1)
    {
        glUniform1i(location, hasColor ? 1 : 0);
    }

    glDrawArrays(GL_TRIANGLES, 0, vertexCount);

    glBindVertexArray(0);
}

GLuint Model::getVao() const
{
    return vao;
}
