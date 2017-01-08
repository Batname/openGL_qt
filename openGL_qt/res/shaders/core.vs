#version 330 core

layout (location = 0) in vec3 vertexPositionModel;
layout (location = 1) in vec3 vertexColor;
layout (location = 2) in vec3 normalModel;

uniform vec3 ambientLight;

uniform mat4 modelToProjectionMatrix;
uniform mat4 modelToWorldMatrix;


out vec3 normalWorld;
out vec3 vertexPositionWorld;

void main()
{
    vec4 v = vec4(vertexPositionModel, 1.0);
    gl_Position = modelToProjectionMatrix * v;
    normalWorld = vec3(modelToWorldMatrix * vec4(normalModel, 0.0f));
    vertexPositionWorld = vec3(modelToWorldMatrix * v);
}
