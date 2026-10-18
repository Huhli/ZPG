
#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 attribute1;
layout(location = 2) in vec3 attribute2;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

uniform bool useTreeColors;
uniform bool useVertexColor;
uniform bool useGroundColor;

out vec3 vertexNormal;
out vec3 vertexColor;

void main()
{
    gl_Position = projectionMatrix
                * viewMatrix
                * modelMatrix
                * vec4(position, 1.0);

    if (useVertexColor)
    {
        // Use colors stored in the model.
        vertexColor = attribute1;
        vertexNormal = attribute2;
    }
    else
    {
        vertexNormal = attribute1;

        if (useGroundColor)
        {
            // Green forest ground.
            vertexColor = vec3(0.12, 0.30, 0.08);
        }
        else if (useTreeColors)
        {
            if (gl_VertexID < 36443)
            {
                // Brown trunk and branches.
                vertexColor = vec3(0.30, 0.16, 0.07);
            }
            else
            {
                // Natural green foliage with subtle variation.
                float variation = 0.92
                    + 0.08 * sin(
                        position.x * 83.0
                        + position.y * 57.0
                        + position.z * 71.0
                    );

                vertexColor = vec3(0.12, 0.42, 0.08)
                            * variation;
            }
        }
        else
        {
            // Default color.
            vertexColor = vec3(1.0);
        }
    }
}
