#version 330 core

in vec3 worldPosition;
in vec3 worldNormal;

uniform vec3 objectColor;
uniform vec3 lightPosition = vec3(0.0, 0.0, 0.0);
uniform vec3 lightColor = vec3(1.0, 1.0, 1.0);

out vec4 out_Color;

void main()
{
    vec3 N = normalize(worldNormal);
    vec3 L = normalize(lightPosition - worldPosition);

    float diffuseFactor = max(dot(N, L), 0.0);

    vec3 diffuse = objectColor * lightColor * diffuseFactor;

    out_Color = vec4(diffuse, 1.0);
}