#include "CameraComponent.h"
#include "../ext/glm/gtc/matrix_transform.hpp"

namespace engine
{
	CameraComponent::CameraComponent(TransformComponent* transform, const float fov,
		const float width, const float height, const float far, const float near) :
		m_transform(transform), m_fov(fov), m_far(far), m_near(near), m_width(width), m_height(height),
		m_perspective(true), m_projection(glm::perspective(glm::radians(fov), width / height, near, far)),
		m_view(glm::lookAt(m_transform->GetPosition(), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)))
	{
	}

	CameraComponent::CameraComponent(const float fov, const float width, const float height,
		const float far, const float near) :
		m_transform(new TransformComponent()),
		m_fov(fov), m_far(far), m_near(near), m_width(width), m_height(height),
		m_perspective(true), m_projection(glm::perspective(glm::radians(fov), width / height, near, far)),
		m_view(glm::lookAt(m_transform->GetPosition(), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)))
	{
	}

	CameraComponent::CameraComponent(TransformComponent* transform, const float width,
		const float height, const float far, const float near) :
		m_transform(transform), m_fov(0), m_far(far), m_near(near), m_width(width), m_height(height),
		m_perspective(false), m_projection(glm::ortho(0.0f, width, 0.0f, height, near, far)),
		m_view(glm::lookAt(m_transform->GetPosition(), glm::vec3(0.0f), glm::vec3(0, 1, 0)))
	{
	}

	CameraComponent::CameraComponent(const float width, const float height,
		const float far, const float near) :
		m_transform(new TransformComponent()), m_fov(0), m_far(far), m_near(near), m_width(width), m_height(height),
		m_perspective(false), m_projection(glm::ortho(0.0f, width, 0.0f, height, near, far)),
		m_view(glm::lookAt(m_transform->GetPosition(), glm::vec3(0.0f), glm::vec3(0, 1, 0)))
	{
	}

	CameraComponent::~CameraComponent()
		= default;

	TransformComponent* CameraComponent::GetTransform() const {return m_transform;}
	float CameraComponent::GetFov() const {return m_fov;}
	float CameraComponent::GetFar() const {return m_far;}
	float CameraComponent::GetNear() const {return m_near;}
	float CameraComponent::GetWidth() const {return m_width;}
	float CameraComponent::GetHeight() const {return m_height;}

	glm::mat4 CameraComponent::GetProjection() const
	{
		return glm::perspective(glm::radians(m_fov), m_width / m_height, m_near, m_far);
	}

	glm::mat4 CameraComponent::GetView() const
	{
		return glm::lookAt(m_transform->GetPosition(), m_lookat, glm::vec3(0, 1, 0));;
	}

	void CameraComponent::LookAt(glm::vec3 lookAt)
	{
		m_lookat = lookAt;
	}
}
