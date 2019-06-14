//shader vertex
#version 420 core //? #version 420 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 vertexUV;
layout(location = 2) in vec3 normal;

uniform mat4 u_Model;
uniform mat4 u_MVP;

out vec3 FragPos;
out vec2 UV;
out vec3 Normal;

void main()
{
	FragPos = vec3(u_Model * vec4(position, 1.0));

	UV = vertexUV;
	Normal = normal;

	gl_Position = u_MVP * vec4(position, 1.0);
};