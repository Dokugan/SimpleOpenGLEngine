#pragma once
#include "Component.h"
#include "../ext/glm/glm.hpp"

namespace engine {
	class TransformComponent :
		public Component
	{
		glm::vec3 m_position;
		glm::vec3 m_rotation;
		float m_scale;

	public:
		TransformComponent();
		TransformComponent(glm::vec3 position);
		TransformComponent(glm::vec3 position, glm::vec3 rotation);

		glm::vec3 GetPosition() const;

		void SetScale(float scale);
		void SetRotation(glm::vec3 rotation);

		void Rotate(glm::vec3 rotation);
		void Scale(float scale);
		void Translate(glm::vec3 destination);
	};
}
