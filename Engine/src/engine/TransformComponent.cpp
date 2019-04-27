#include "TransformComponent.h"
#include "../ext/glm/glm.hpp"
#include "../ext/glm/gtx/transform.hpp"
#include "../ext/glm/gtc/quaternion.hpp"
#include "../ext/glm/gtx/matrix_decompose.hpp"
#include "../ext/glm/gtx/quaternion.hpp"


namespace engine {

	glm::mat4 GetIdentityMatrix()
	{
		return glm::mat4(1.f, 0.f, 0.f, 0.f,
			0.f, 1.f, 0.f, 0.f,
			0.f, 0.f, 1.f, 0.f,
			0.f, 0.f, 0.f, 1.f);
	}

	TransformComponent::TransformComponent()
	{
		m_model_matrix = GetIdentityMatrix();
	}

	TransformComponent::TransformComponent(glm::vec3 position)		
	{
		m_model_matrix = GetIdentityMatrix();
		m_model_matrix = glm::translate(m_model_matrix, position);
	}

	TransformComponent::TransformComponent(glm::vec3 position, glm::quat rotation)
	{
		m_model_matrix = GetIdentityMatrix();
		m_model_matrix = glm::translate(m_model_matrix, position);
		//m_model_matrix = Rotate()
	}

	glm::mat4 TransformComponent::GetModelMatrix() const { return m_model_matrix; }

	glm::vec3 TransformComponent::GetPosition() const
	{
		glm::vec3 scale;
		glm::quat rotation = glm::quat(0,0,0,0);
		glm::vec3 translation;
		glm::vec3 skew;
		glm::vec4 perspective = glm::vec4(0);
		glm::decompose(m_model_matrix, scale, rotation, translation, skew, perspective);
		return translation;
	}

	glm::quat TransformComponent::GetRotation() const
	{
		glm::vec3 scale;
		glm::quat rotation = glm::quat(0, 0, 0, 0);
		glm::vec3 translation;
		glm::vec3 skew;
		glm::vec4 perspective = glm::vec4(0);
		glm::decompose(m_model_matrix, scale, rotation, translation, skew, perspective);
		return rotation;
	}

	void TransformComponent::Scale(glm::vec3 scale)
	{
		m_model_matrix = glm::scale(m_model_matrix, scale);
	}

	// void TransformComponent::Rotate(glm::quat rotation)
	// {
	// }

	void TransformComponent::Rotate(glm::vec3 axis, float radians)
	{
		m_model_matrix = glm::rotate(m_model_matrix, radians, axis);
	}

	void TransformComponent::Translate(glm::vec3 movement)
	{
		m_model_matrix = glm::translate(m_model_matrix, movement);
	}
}
