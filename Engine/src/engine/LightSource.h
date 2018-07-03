#pragma once
#include "../vendor/glm/detail/type_vec3.hpp"

namespace engine {
	class LightSource
	{
		glm::vec3 m_color;
		float m_intensity;
	public:
		LightSource();
		virtual ~LightSource();
	};
}
