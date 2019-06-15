//shader fragment
#version 420 core //? #version 420 core

struct Material {
	//vec3 diffuse;
	//vec3 specular;
	float shininess;
};

struct DirLight {
	vec3 direction;
	vec3 diffuse;
	vec3 specular;
};

in vec3 FragPos;
in vec2 UV;
in vec3 Normal;

out vec4 FragColour;

// Values that stay constant for the whole mesh.
uniform sampler2D u_TextureSampler;
uniform float u_AmbientIntensity;
uniform vec3 u_AmbientColour;
uniform int u_NumDirLights;
uniform Material u_Material;
uniform DirLight u_DirectionalLights[1];
uniform vec3 u_ViewPos;

vec3 CalcDirLight(DirLight light, vec3 viewDir) 
{
	vec3 lightDir = normalize(-light.direction);
	//diffuse lighting
	float diff = max(dot(lightDir, Normal), 0.0);
	
	//specular lighting

	vec3 reflectDir = reflect(-lightDir, Normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), u_Material.shininess);
	//combine
	vec3 ambient = (u_AmbientColour * u_AmbientIntensity) * vec3(texture(u_TextureSampler, UV));
	vec3 diffuse = light.diffuse  * diff * vec3(texture(u_TextureSampler, UV));
	vec3 specular = light.specular * spec * vec3(texture(u_TextureSampler, UV));
	return (ambient + diffuse + specular);
}

void main()
{
	vec3 result = vec3(0.0);

	for (int i = 0; i < u_NumDirLights; i++){
		vec3 viewDir = normalize(u_ViewPos - FragPos);
		result += CalcDirLight(u_DirectionalLights[i], viewDir);
	}
	
	FragColour = vec4(result, 1.0);
};