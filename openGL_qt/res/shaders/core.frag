#version 330 core

in vec3 ourColor;
out vec4 color;

uniform vec3 ambientLight;

void main()
{
    color = vec4(ourColor * ambientLight, 1.0f);
}
