#pragma once
#include "../ext/glm/detail/type_vec3.hpp"
#include "GameObject.h"

namespace engine {

	class DirectionalLight;

	struct LightSources
	{
		std::vector<DirectionalLight> directionalLights;
		//TODO std::vector<SpotLight*> spotlights;
		//TODO std::vector<PointLight*> pointLights;
	};

	class LightSource : public GameObject
	{
	public:
		glm::vec3 m_diffuse;
		glm::vec3 m_specular;

		LightSource();
		virtual ~LightSource();
	};
}
