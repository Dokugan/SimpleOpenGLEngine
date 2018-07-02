#shader vertex
#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 vertexUV;

uniform mat4 u_MVP;

out vec2 UV;

void main()
{
	gl_Position = u_MVP * vec4(position.x, position.y, position.z, 1);

	UV = vertexUV;
};

#shader fragment
#version 330 core

in vec2 UV;

out vec4 color;

uniform sampler2D textureSampler;

void main()
{
	color = texture(textureSampler, UV);
};