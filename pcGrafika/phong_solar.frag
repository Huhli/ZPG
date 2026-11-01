
#version 330 core

in vec3 worldPosition;
in vec3 worldNormal;
in vec3 surfaceColor;

uniform vec3 objectColor;
uniform vec3 lightPosition;
uniform vec3 lightColor;
uniform vec3 viewPosition;

out vec4 out_Color;

void main()
{
    vec3 N = normalize(worldNormal);
    vec3 L = normalize(lightPosition - worldPosition);
    vec3 V = normalize(viewPosition - worldPosition);

    float distanceToLight = length(lightPosition - worldPosition);
    float attenuation = 1.0 / (
        1.0 + 0.12 * distanceToLight
            + 0.045 * distanceToLight * distanceToLight
    );

    // Zachová pùvodní barvy modelu.
    vec3 baseColor = surfaceColor * objectColor;

    vec3 ambient = 0.28 * baseColor;

    float diffuseFactor = max(dot(N, L), 0.0);
    vec3 diffuse = diffuseFactor * baseColor * lightColor;

    vec3 R = reflect(-L, N);
    float specularFactor = 0.0;

    if (diffuseFactor > 0.0)
        specularFactor = pow(max(dot(R, V), 0.0), 48.0);

    vec3 specular = 0.5 * specularFactor * lightColor;

    vec3 result = ambient + attenuation * (diffuse + specular);

    out_Color = vec4(clamp(result, 0.0, 1.0), 1.0);
}
