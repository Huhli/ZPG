#version 330 core

in vec3 vertexNormal;

out vec4 fragColor;

void main()
{
    vec3 color = abs(vertexNormal);

    fragColor = vec4(color, 1.0);
}