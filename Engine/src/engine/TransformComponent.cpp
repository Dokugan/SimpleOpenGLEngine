#include "TransformComponent.h"
#include "../ext/glm/glm.hpp"
#include "../ext/glm/gtx/transform.hpp"
#include "../ext/glm/gtc/quaternion.hpp"
#include "../ext/glm/gtx/matrix_decompose.hpp"
#include "../ext/glm/gtx/quaternion.hpp"
#include "../ext/glm/gtx/rotate_vector.hpp"


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
		//m_model_matrix = GetIdentityMatrix();
		m_rotation = glm::quat(1,0,0,0);
		m_position = glm::vec3(0, 0, 0);
		m_scale = glm::vec3(1, 1, 1);
	}

	TransformComponent::TransformComponent(glm::vec3 position)		
	{
		m_position = position;
		m_rotation = glm::quat(1, 0, 0, 0);
		m_scale = glm::vec3(1, 1, 1);
		//m_model_matrix = GetIdentityMatrix();
		//m_model_matrix = glm::translate(m_model_matrix, position);
	}

	TransformComponent::TransformComponent(glm::vec3 position, glm::quat rotation)
	{
		m_position = position;
		m_rotation = rotation;
		m_scale = glm::vec3(1, 1, 1);
		//m_model_matrix = GetIdentityMatrix();
		//m_model_matrix = glm::translate(m_model_matrix, position);
		//m_model_matrix = Rotate()
	}

	glm::mat4 TransformComponent::GetModelMatrix() const
	{
		glm::mat4 translationMat = GetIdentityMatrix();
		translationMat = glm::translate(translationMat, m_position);
		// get rotation matrix from rotation
		float angle = 2 * acos(m_rotation.w);
		glm::mat4 rotationMat;
		// when angle = 0 divide by 0 error occurs
		if (angle != 0.f)
		{
			rotationMat = glm::rotate(GetIdentityMatrix(), angle, glm::vec3(
				m_rotation.x / sqrt(1 - m_rotation.w * m_rotation.w),
				m_rotation.y / sqrt(1 - m_rotation.w * m_rotation.w),
				m_rotation.z / sqrt(1 - m_rotation.w * m_rotation.w)));
		}
		else { rotationMat = GetIdentityMatrix(); }

		glm::mat4 modelMatrix = translationMat * rotationMat;
		modelMatrix = glm::scale(modelMatrix, m_scale);
		return modelMatrix;
	}

	glm::vec3 TransformComponent::GetPosition() const
	{
		return m_position;
	}

	glm::quat TransformComponent::GetRotation() const
	{
		return m_rotation;
	}

	void TransformComponent::Scale(glm::vec3 scale)
	{
		m_scale = scale;
		//m_model_matrix = glm::scale(m_model_matrix, scale);
	}

	// void TransformComponent::Rotate(glm::quat rotation)
	// {
	// }

	void TransformComponent::Rotate(glm::vec3 axis, float angle)
	{
		m_rotation = glm::rotate(m_rotation, angle, axis);
		//m_model_matrix = glm::rotate(m_model_matrix, radians, axis);
	}

	void TransformComponent::RotateEuler(glm::vec3 rotation)
	{
		glm::vec3 euler = glm::eulerAngles(m_rotation);
		euler -= rotation;
		glm::quat quat = glm::quat(euler);
		m_rotation = quat;
	}

	void TransformComponent::Translate(glm::vec3 movement)
	{
		m_position += movement;
	}
}
