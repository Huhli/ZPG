#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;

uniform mat4 modelMatrix = mat4(1.0);
uniform mat4 viewMatrix = mat4(1.0);
uniform mat4 projectionMatrix = mat4(1.0);

// 0 = bez transformace
// 1 = chybná transformace
// 2 = správná transformace
uniform int normalMode = 2;

out vec3 worldPosition;
out vec3 worldNormal;

void main()
{
    vec4 worldPos = modelMatrix * vec4(position, 1.0);

    worldPosition = worldPos.xyz;

    if (normalMode == 0)
    {
        worldNormal = normalize(normal);
    }
    else if (normalMode == 1)
    {
        worldNormal = normalize(mat3(modelMatrix) * normal);
    }
    else
    {
        mat3 normalMatrix = transpose(inverse(mat3(modelMatrix)));
        worldNormal = normalize(normalMatrix * normal);
    }

    gl_Position = projectionMatrix * viewMatrix * worldPos;
}