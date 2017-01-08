#version 330 core

layout (location = 0) in vec3 vertexPositionModel;
layout (location = 1) in vec3 vertexColor;
layout (location = 2) in vec3 normalModel;

uniform vec3 ambientLight;

uniform mat4 fullTransformMatrix;
uniform mat4 modelToWorldTransformMatrix;


out vec3 theNormal;
out vec3 thePosition;

void main()
{
    vec4 v = vec4(vertexPositionModel, 1.0);
    gl_Position = fullTransformMatrix * v;
    theNormal = vec3(modelToWorldTransformMatrix * vec4(normalModel, 0.0f));
    thePosition = vec3(modelToWorldTransformMatrix * v);
}
