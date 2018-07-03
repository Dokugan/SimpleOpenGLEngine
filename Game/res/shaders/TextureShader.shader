#shader vertex
#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 vertexUV;
layout(location = 2) in vec3 normal;

uniform mat4 u_MVP;
uniform mat4 u_V;
uniform mat4 u_M;
uniform vec3 u_LightPosition_worldspace;

out vec2 UV;
out vec3 Position_worldspace;
out vec3 Normal_cameraspace;
out vec3 EyeDirection_cameraspace;
out vec3 LightDirection_cameraspace;

void main()
{
	gl_Position = u_MVP * vec4(position.x, position.y, position.z, 1);

	// Position of the vertex, in worldspace : M * position
	Position_worldspace = (M * vec4(vertexPosition_modelspace, 1)).xyz;

	// Vector that goes from the vertex to the camera, in camera space.
	// In camera space, the camera is at the origin (0,0,0).
	vec3 vertexPosition_cameraspace = (V * M * vec4(vertexPosition_modelspace, 1)).xyz;
	EyeDirection_cameraspace = vec3(0, 0, 0) - vertexPosition_cameraspace;

	// Vector that goes from the vertex to the light, in camera space. M is ommited because it's identity.
	vec3 LightPosition_cameraspace = (V * vec4(LightPosition_worldspace, 1)).xyz;
	LightDirection_cameraspace = LightPosition_cameraspace + EyeDirection_cameraspace;

	// Normal of the the vertex, in camera space
	Normal_cameraspace = (V * M * vec4(vertexNormal_modelspace, 0)).xyz; // Only correct if ModelMatrix does not scale the model ! Use its inverse transpose if not.

	UV = vertexUV;
};

//====================================================================================================================================================

#shader fragment
#version 330 core

in vec2 UV;
in vec3 Position_worldspace;
in vec3 Normal_cameraspace;
in vec3 EyeDirection_cameraspace;
in vec3 LightDirection_cameraspace;

out vec4 color;

// Values that stay constant for the whole mesh.
uniform sampler2D u_TextureSampler;
uniform vec3 u_LightPosition_worldspace;
uniform float u_LightIntensity;
uniform vec3 u_LightColor;

void main()
{

	// Material properties
	vec3 MaterialDiffuseColor = texture(u_textureSampler, UV).rgb;
	vec3 MaterialAmbientColor = vec3(0.1, 0.1, 0.1) * MaterialDiffuseColor;
	vec3 MaterialSpecularColor = vec3(0.3, 0.3, 0.3);

	// Distance to the light
	float distance = length(u_LightPosition_worldspace - Position_worldspace);

	// Normal of the computed fragment, in camera space
	vec3 n = normalize(Normal_cameraspace);
	// Direction of the light (from the fragment to the light)
	vec3 l = normalize(LightDirection_cameraspace);
	// Cosine of the angle between the normal and the light direction, 
	// clamped above 0
	//  - light is at the vertical of the triangle -> 1
	//  - light is perpendicular to the triangle -> 0
	//  - light is behind the triangle -> 0
	float cosTheta = clamp(dot(n, l), 0, 1);

	// Eye vector (towards the camera)
	vec3 E = normalize(EyeDirection_cameraspace);
	// Direction in which the triangle reflects the light
	vec3 R = reflect(-l, n);
	// Cosine of the angle between the Eye vector and the Reflect vector,
	// clamped to 0
	//  - Looking into the reflection -> 1
	//  - Looking elsewhere -> < 1
	float cosAlpha = clamp(dot(E, R), 0, 1);

	color =
		// Ambient : simulates indirect lighting
		MaterialAmbientColor +
		// Diffuse : "color" of the object
		MaterialDiffuseColor * u_LightColor * u_LightIntensity * cosTheta / (distance*distance) +
		// Specular : reflective highlight, like a mirror
		MaterialSpecularColor * u_LightColor * u_LightIntensity * pow(cosAlpha, 5) / (distance*distance);
};