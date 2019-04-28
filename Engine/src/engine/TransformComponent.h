#pragma once
#include "Component.h"
#include "../ext/glm/glm.hpp"
#include "../ext/glm/gtc/quaternion.hpp"

namespace engine {
	glm::mat4 GetIdentityMatrix();

	class TransformComponent :
		public Component
	{
		glm::vec3 m_position;
		glm::quat m_rotation;
		glm::vec3 m_scale;
		//glm::mat4 m_model_matrix;

	public:
		TransformComponent();
		TransformComponent(glm::vec3 position);
		TransformComponent(glm::vec3 position, glm::quat rotation);

		glm::mat4 GetModelMatrix() const;
		glm::vec3 GetPosition() const;
		glm::quat GetRotation() const;

		void Rotate(glm::vec3 axis, float radians);
		//void Rotate(glm::quat rotation);
		void Scale(glm::vec3 scale);
		void Translate(glm::vec3 movement);
	};
}
