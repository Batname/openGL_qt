#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;
layout (location = 2) in vec3 normal;


uniform mat4 fullTransformMatrix;
uniform vec3 ambientLight;
uniform vec3 lightPosition;

out vec3 ourColor;

void main()
{
    vec4 v = vec4(position, 1.0);
    gl_Position = fullTransformMatrix * v;
    vec3 lightVector = normalize(lightPosition - position);
    float brightness = dot(lightVector, normal);
    ourColor = vec3(brightness, brightness, brightness);
}
