#pragma once
#include "../ext/glm/detail/type_vec3.hpp"
#include "Component.h"

namespace engine {
	class Component;

	class LightSource : public Component
	{
		glm::vec3 m_color;
		float m_intensity;
	public:
		LightSource();
		virtual ~LightSource();
	};
}
