
#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 vertexColor;
layout (location = 2) in vec3 normal;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

out vec3 worldPosition;
out vec3 worldNormal;
out vec3 surfaceColor;

void main()
{
    vec4 worldPos = modelMatrix * vec4(position, 1.0);

    worldPosition = worldPos.xyz;
    worldNormal = normalize(
        mat3(transpose(inverse(modelMatrix))) * normal
    );

    surfaceColor = vertexColor;

    gl_Position = projectionMatrix * viewMatrix * worldPos;
}
