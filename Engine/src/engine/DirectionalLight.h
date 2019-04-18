#pragma once
#include "LightSource.h"
#include "../ext/glm/glm.hpp"

namespace engine {
	class DirectionalLight :
		public LightSource
	{
		glm::vec3 m_direction;
	public:
		DirectionalLight();
		~DirectionalLight();
	};
}
