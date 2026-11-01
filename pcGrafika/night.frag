#version 330 core

in vec3 worldPosition;
in vec3 worldNormal;

uniform vec3 objectColor;
uniform vec3 lightPosition;
uniform vec3 lightColor;
uniform vec3 viewPosition;

// Koeficienty útlumu svìtla
uniform float constantAttenuation;
uniform float linearAttenuation;
uniform float quadraticAttenuation;

out vec4 out_Color;

void main()
{
    vec3 N = normalize(worldNormal);
    vec3 L = normalize(lightPosition - worldPosition);
    vec3 V = normalize(viewPosition - worldPosition);

    float distanceToLight = length(lightPosition - worldPosition);

    float attenuation = 1.0 / (
        constantAttenuation +
        linearAttenuation * distanceToLight +
        quadraticAttenuation * distanceToLight * distanceToLight
    );

    // Slabé okolní svìtlo
    vec3 ambient = 0.035 * objectColor;

    // Difuzní složka
    float diffuseFactor = max(dot(N, L), 0.0);
    vec3 diffuse = diffuseFactor * objectColor * lightColor;

    // Zrcadlová složka
    vec3 R = reflect(-L, N);
    float specularFactor = 0.0;

    if (diffuseFactor > 0.0)
    {
        specularFactor = pow(max(dot(R, V), 0.0), 16.0);
    }

    vec3 specular = 0.15 * specularFactor * lightColor;

    vec3 result = ambient + attenuation * (diffuse + specular);

    out_Color = vec4(result, 1.0);
}