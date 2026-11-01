
#version 330 core

out vec4 FragColor;

void main()
{
    // Vlastní záøe družice – nezávislá na svìtle Slunce.
    vec3 glowColor = vec3(1.0, 0.85, 0.25);

    FragColor = vec4(glowColor, 1.0);
}
