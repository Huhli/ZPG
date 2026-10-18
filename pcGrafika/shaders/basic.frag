
#version 330 core

in vec3 vertexNormal;
in vec3 vertexColor;

uniform bool useTreeColors;
uniform bool useVertexColor;
uniform bool useGroundColor;

out vec4 fragColor;

void main()
{
    vec3 normal = normalize(vertexNormal);

    vec3 lightDirection = normalize(
        vec3(0.4, 0.8, 0.3)
    );

    float diffuse = max(
        dot(normal, lightDirection),
        0.0
    );

    float light = 0.40 + 0.60 * diffuse;

    if (useTreeColors || useGroundColor)
    {
        // Apply lighting to trees and ground.
        fragColor = vec4(vertexColor * light, 1.0);
    }
    else if (useVertexColor)
    {
        // Preserve colors stored in other models.
        fragColor = vec4(vertexColor, 1.0);
    }
    else
    {
        // Default shading.
        vec3 color = abs(normal);
        fragColor = vec4(color * light, 1.0);
    }
}
