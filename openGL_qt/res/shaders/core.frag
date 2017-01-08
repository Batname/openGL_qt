#version 330 core

in vec3 normalWorld;
in vec3 vertexPositionWorld;

out vec4 color;

uniform vec3 lightPositionWorld;

void main()
{
    vec3 lightVectorWorld = normalize(lightPositionWorld - vertexPositionWorld);
    float brightness = dot(lightVectorWorld, normalize(normalWorld));
    color = vec4(brightness, brightness, brightness, 1.0);
}
