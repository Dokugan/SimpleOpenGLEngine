#pragma once
#include "LightSource.h"
#include "../ext/glm/glm.hpp"

namespace engine {
	class DirectionalLight : public LightSource
	{
	public:
		glm::vec3 m_direction;

		DirectionalLight(glm::vec3 direction, glm::vec3 diffuse, glm::vec3 specular);
		~DirectionalLight();
	};
}
