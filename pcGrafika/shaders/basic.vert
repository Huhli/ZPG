#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;

uniform vec3 translation;
uniform float scale;
uniform float rotationY;

out vec3 vertexNormal;

void main()
{
    vec3 pos = position;

    // Scale
    pos *= scale;

    // Rotation around Y axis
    float c = cos(rotationY);
    float s = sin(rotationY);

    float x = c * pos.x + s * pos.z;
    float y = pos.y;
    float z = -s * pos.x + c * pos.z;

    pos = vec3(x, y, z);

    // Translation
    pos += translation;

    gl_Position = vec4(pos, 1.0);

    vertexNormal = normal;
}