#shader vertex
#version 420 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 vertexUV;
layout(location = 2) in vec3 normal;

uniform mat4 u_MVP;

out vec2 UV;
out vec3 Normal;

void main()
{
	gl_Position = u_MVP * vec4(position.x, position.y, position.z, 1);

	UV = vertexUV;
	Normal = normal;
};

//====================================================================================================================================================

#shader fragment
#version 420 core

in vec2 UV;
in vec3 Normal;

out vec4 colour;

// Values that stay constant for the whole mesh.
uniform sampler2D u_TextureSampler;
uniform float u_AmbientIntensity;
uniform vec3 u_AmbientColour;
uniform vec3 u_DirectionalLights[1];

void main()
{
	vec4 texColour = texture(u_TextureSampler, UV);
	vec3 ambient = u_AmbientColour * u_AmbientIntensity;
	colour = texColour * vec4(ambient, 1.0);
};