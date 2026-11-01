#version 330 core

in vec3 worldPosition;
in vec3 worldNormal;

uniform vec3 objectColor;
uniform vec3 lightPosition = vec3(0.0, 0.0, 0.0);
uniform vec3 lightColor = vec3(1.0, 1.0, 1.0);
uniform vec3 viewPosition = vec3(0.0, 0.0, 3.0);

uniform float shininess = 1.0;

out vec4 out_Color;

void main()
{
    vec3 N = normalize(worldNormal);
    vec3 L = normalize(lightPosition - worldPosition);
    vec3 V = normalize(viewPosition - worldPosition);

    vec3 ambient = 0.1 * objectColor;

    float diffuseFactor = max(dot(N, L), 0.0);
    vec3 diffuse = diffuseFactor * objectColor * lightColor;

    vec3 R = reflect(-L, N);

    // Zrcadlová složka bez kontroly odvrácené strany
    float specularFactor = 0.0;

    if (diffuseFactor > 0.0)
    {
        specularFactor = pow(
            max(dot(R, V), 0.0),
            shininess
        );
    }

    vec3 specular = 0.7 * specularFactor * lightColor;

    vec3 result = ambient + diffuse + specular;

    out_Color = vec4(result, 1.0);
}