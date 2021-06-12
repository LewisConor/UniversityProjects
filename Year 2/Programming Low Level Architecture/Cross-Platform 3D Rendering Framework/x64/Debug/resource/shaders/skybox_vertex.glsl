#version 330 core

layout(location = 0) in vec3 aPos;

out vec3 texCoords;

uniform mat4 ProjectionViewMatrix;

void main()
{
	texCoords = aPos;
	gl_Position = (ProjectionViewMatrix * vec4(aPos * 1000.0, 1.0)).xyww;
}