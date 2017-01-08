#version 330 core

in vec3 theNormal;
in vec3 thePosition;

out vec4 color;

uniform vec3 lightPosition;

void main()
{
    vec3 lightVector = normalize(lightPosition - thePosition);
    float brightness = dot(lightVector, theNormal);
    color = vec4(brightness, brightness, brightness, 1.0);
}
