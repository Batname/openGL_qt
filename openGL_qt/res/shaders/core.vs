#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;

uniform vec3 dominatingColor;
uniform float yFlip;

out vec3 ourColor;

void main()
{
    gl_Position = vec4(position.x, position.y, position.z, 1.0);
    gl_Position.y = gl_Position.y * yFlip;
    ourColor = dominatingColor;
}
