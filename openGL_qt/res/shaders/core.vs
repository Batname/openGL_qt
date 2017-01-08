#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 vertexColor;
layout (location = 2) in vec3 normal;


uniform mat4 fullTransformMatrix;
uniform vec3 ambientLight;


out vec3 theNormal;
out vec3 thePosition;

void main()
{
    vec4 v = vec4(position, 1.0);
    gl_Position = fullTransformMatrix * v;
    theNormal = normal;
    thePosition = position;
}
