#include "DirectionalLight.h"

namespace engine {
	DirectionalLight::DirectionalLight(glm::vec3 direction, glm::vec3 diffuse, glm::vec3 specular):
		m_direction(direction)
	{
		m_diffuse = diffuse;
		m_specular = specular;
	}


	DirectionalLight::~DirectionalLight()
	{
	}
}
