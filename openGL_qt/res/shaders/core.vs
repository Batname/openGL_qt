#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;

uniform mat4 modelTransformMatrix;
uniform mat4 projectionMatrix;
out vec3 ourColor;

void main()
{
    vec4 v = vec4(position, 1.0);
    vec4 newPosition = modelTransformMatrix * v;
    vec4 projectionPosition = projectionMatrix * newPosition;
    gl_Position = projectionPosition;
    
    ourColor = color;
}
