
#version 330 core

in vec3 worldPosition;
in vec3 worldNormal;

uniform vec3 objectColor;

out vec4 out_Color;

void main()
{
    vec3 ambient = objectColor * 0.65;
    out_Color = vec4(ambient, 1.0);
}
