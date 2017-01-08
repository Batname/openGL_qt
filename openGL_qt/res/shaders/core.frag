#version 330 core

in vec3 normalWorld;
in vec3 vertexPositionWorld;

out vec4 daColor;

uniform vec4 ambientLight;
uniform vec3 lightPositionWorld;

void main()
{
    vec3 lightVectorWorld = normalize(lightPositionWorld - vertexPositionWorld);
    float brightness = dot(lightVectorWorld, normalize(normalWorld));
    vec4 deffuseLight = vec4(brightness, brightness, brightness, 1.0);
    daColor = clamp(deffuseLight, 0, 1) + ambientLight;
}
