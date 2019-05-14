#pragma once
#include "../ext/glm/detail/type_vec3.hpp"
#include "GameObject.h"

namespace engine {

	class LightSource : public GameObject
	{
		glm::vec3 m_color;
		float m_intensity;
	public:
		LightSource();
		virtual ~LightSource();
	};
}
