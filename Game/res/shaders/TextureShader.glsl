#shader vertex
#version 420 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 vertexUV;
layout(location = 2) in vec3 normal;

uniform mat4 u_MVP;

out vec2 UV;

void main()
{
	gl_Position = u_MVP * vec4(position.x, position.y, position.z, 1);

	UV = vertexUV;
};

//====================================================================================================================================================

#shader fragment
#version 420 core

in vec2 UV;

out vec4 color;

// Values that stay constant for the whole mesh.
uniform sampler2D u_TextureSampler;

void main()
{
	color = texture(u_TextureSampler, UV);
};