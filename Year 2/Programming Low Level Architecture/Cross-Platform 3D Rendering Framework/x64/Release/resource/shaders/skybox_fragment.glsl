#version 330 core

out vec4 fragColour;

in vec3 texCoords;

uniform samplerCube skybox;

void main()
{
	fragColour = texture(skybox, texCoords);
}