#include "Camera.h"
#include "../vendor/glm/gtc/matrix_transform.hpp"

namespace engine
{
	Camera::Camera(const Transform& transform, const float fov,
		const float width, const float height, const float far, const float near) :
		m_transform(transform), m_fov(fov), m_far(far), m_near(near), m_width(width), m_height(height),
		m_perspective(true), m_projection(glm::perspective(glm::radians(fov), width / height, near, far)),
		m_view(glm::lookAt(m_transform.GetPosition(), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)))
	{
	}

	Camera::Camera(const float fov, const float width, const float height,
		const float far, const float near) :
		m_fov(fov), m_far(far), m_near(near), m_width(width), m_height(height),
		m_perspective(true), m_projection(glm::perspective(glm::radians(fov), width / height, near, far)),
		m_view(glm::lookAt(m_transform.GetPosition(), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0)))
	{
	}

	Camera::Camera(const Transform& transform, const float width,
		const float height, const float far, const float near) :
		m_transform(transform), m_fov(0), m_far(far), m_near(near), m_width(width), m_height(height),
		m_perspective(false), m_projection(glm::ortho(0.0f, width, 0.0f, height, near, far)),
		m_view(glm::lookAt(m_transform.GetPosition(), glm::vec3(0.0f), glm::vec3(0, 1, 0)))
	{
	}

	Camera::Camera(const float width, const float height,
		const float far, const float near) :
		m_transform(Transform()), m_fov(0), m_far(far), m_near(near), m_width(width), m_height(height),
		m_perspective(false), m_projection(glm::ortho(0.0f, width, 0.0f, height, near, far)),
		m_view(glm::lookAt(m_transform.GetPosition(), glm::vec3(0.0f), glm::vec3(0, 1, 0)))
	{
	}

	Camera::~Camera()
		= default;

	Transform& Camera::GetTransform()
	{
		return m_transform;
	}

	glm::mat4 Camera::GetProjection() const
	{
		return glm::perspective(glm::radians(m_fov), m_width / m_height, m_near, m_far);
	}

	glm::mat4 Camera::GetView() const
	{
		return glm::lookAt(m_transform.GetPosition(), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	}

	void Camera::LookAt(glm::vec3 lookAt)
	{
		m_view = glm::lookAt(m_transform.GetPosition(), lookAt, glm::vec3(0,1,0));
	}
}
