#pragma once
#include "Component.h"
#include "../../ext/glm/glm.hpp"
#include "../../ext/glm/gtc/quaternion.hpp"
# define PI		3.14159265358979323846

namespace engine {
	glm::mat4 GetIdentityMatrix();

	class TransformComponent :
		public Component
	{
		glm::vec3 m_position;
		glm::quat m_rotation;
		glm::vec3 m_scale;

	public:
		TransformComponent();
		TransformComponent(glm::vec3 position);
		TransformComponent(glm::vec3 position, glm::quat rotation);

		glm::mat4 GetModelMatrix() const;
		glm::vec3 GetPosition() const;
		glm::quat GetRotation() const;

		glm::vec3 Forward() const;
		glm::vec3 Right() const;
		glm::vec3 Up() const;
		glm::vec3 RelativeVec(glm::vec3 v) const;

		void Rotate(glm::vec3 axis, float radians);
		void Rotate(float yaw, float pitch, float roll);
		//void Rotate(glm::quat rotation);
		void Scale(glm::vec3 scale);
		void Translate(glm::vec3 movement);
	};
}
