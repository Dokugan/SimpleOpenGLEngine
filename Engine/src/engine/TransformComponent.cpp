#include "TransformComponent.h"
#include "../ext/glm/gtx/rotate_vector.hpp"


namespace engine {
	TransformComponent::TransformComponent() :
		m_position(glm::vec3(0.0f)), m_rotation(glm::vec3(0.0f)), m_scale(1)
	{
	}

	TransformComponent::TransformComponent(glm::vec3 position) :
		m_position(position), m_rotation(glm::vec3(0.0f)), m_scale(1)
	{
	}

	TransformComponent::TransformComponent(glm::vec3 position, glm::vec3 rotation) :
		m_position(position), m_rotation(rotation), m_scale(1)
	{
	}


	glm::vec3 TransformComponent::GetPosition() const
	{
		return m_position;
	}

	void TransformComponent::SetScale(float scale)
	{
		m_scale = scale;
	}

	void TransformComponent::SetRotation(glm::vec3 rotation)
	{
		m_rotation = rotation;
	}

	// Takes in vector 3 with (x, y, z) rotation in degrees
	//prolly doesnt work
	void TransformComponent::Rotate(glm::vec3 rotation)
	{
		glm::rotate(rotation.x, m_rotation);
		glm::rotate(rotation.y, m_rotation);
		glm::rotate(rotation.z, m_rotation);
	}


	void TransformComponent::Scale(float scale)
	{
		m_scale *= scale;
	}

	void TransformComponent::Translate(glm::vec3 movement)
	{
		m_position += movement;
	}
}
