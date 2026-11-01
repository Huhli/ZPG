
#version 330 core

in vec3 worldPosition;
in vec3 worldNormal;
in vec3 surfaceColor;

out vec4 out_Color;

void main()
{
    // Zachová barvy modelu Slunce a dodá mu teplý odstín.
    vec3 baseColor = surfaceColor * vec3(1.0, 0.72, 0.28);

    // Slunce je samo zdrojem svìtla, proto ho neztmavujeme podle normál.
    vec3 result = baseColor * 1.8;

    // Jemný oranžový nádech a omezení maximálního jasu.
    result = clamp(result, 0.0, 1.0);

    out_Color = vec4(result, 1.0);
}
