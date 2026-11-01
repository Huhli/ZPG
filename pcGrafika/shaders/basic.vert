
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

uniform float hourHandAngle;
uniform float minuteHandAngle;
uniform float secondHandAngle;

// Vertex ranges for the three hands.
uniform int hourHandStart;
uniform int minuteHandStart;
uniform int secondHandStart;

out vec3 vertexNormal;
out vec3 vertexColor;

void main()
{
    vec3 adjustedPosition = position;

    if (useVertexColor)
    {
        int id = gl_VertexID;

        float angle = 0.0;
        bool isHand = false;

        if (id >= hourHandStart && id < hourHandStart + 6)
        {
            angle = hourHandAngle;
            isHand = true;
        }
        else if (id >= minuteHandStart && id < minuteHandStart + 6)
        {
            angle = minuteHandAngle;
            isHand = true;
        }
        else if (id >= secondHandStart && id < secondHandStart + 6)
        {
            angle = secondHandAngle;
            isHand = true;
        }

        if (isHand)
        {
            // Rotate the hand around its base at the clock center.
            float c = cos(angle);
            float s = sin(angle);

            adjustedPosition.xy = vec2(
                c * position.x - s * position.y,
                s * position.x + c * position.y
            );
        }

        vertexColor = attribute1;
        vertexNormal = attribute2;
    }
    else
    {
        vertexNormal = attribute1;

        if (useGroundColor)
        {
            vertexColor = vec3(0.12, 0.30, 0.08);
        }
        else if (useTreeColors)
        {
            if (gl_VertexID < 36443)
            {
                vertexColor = vec3(0.30, 0.16, 0.07);
            }
            else
            {
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
            vertexColor = vec3(1.0);
        }
    }

    gl_Position = projectionMatrix
                * viewMatrix
                * modelMatrix
                * vec4(adjustedPosition, 1.0);
}
