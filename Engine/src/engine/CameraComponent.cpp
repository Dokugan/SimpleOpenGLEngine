#include "CameraComponent.h"
#include "GameObject.h"
#include "../ext/glm/gtc/matrix_transform.hpp"
#include "../ext/glm/gtx/quaternion.hpp"
#include "../ext/glm/gtx/matrix_decompose.hpp"

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

	CameraComponent* CameraComponent::PerspectiveCamera(TransformComponent* transform, const float fov, const float width, const float height, const float far, const float near)
	{
		return new CameraComponent(transform, fov, width, height, far, near);
	}
	CameraComponent* CameraComponent::PerspectiveCamera(const float fov, const float width, const float height, const float far, const float near)
	{
		return new CameraComponent(fov, width, height, far, near);
	}

	CameraComponent* CameraComponent::OrthographicCamera(TransformComponent* transform, const float width, const float height, const float far, const float near)
	{
		return new CameraComponent(transform, width, height, far, near);
	}
	CameraComponent* CameraComponent::OrthographicCamera(const float width, const float height, const float far, const float near)
	{
		return new CameraComponent(width, height, far, near);
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
		//variables for decomposition
		glm::vec3 lookat;
		glm::vec3 scale;
		glm::quat rot = glm::quat(0, 0, 0, 0);
		glm::vec3 skew;
		glm::vec4 perspective = glm::vec4(0);

		//get rotation
		glm::quat rotation = m_transform->GetRotation();
		//get translation matrix
		glm::mat4 translationmat = glm::translate(GetIdentityMatrix(), m_transform->GetPosition());

		// get rotation matrix from rotation
		float angle = 2 * acos(rotation.w);
		glm::mat4 rotationmat;
		// when angle = 0 divide by 0 error occurs
		if (angle != 0.f)
		{
			rotationmat = glm::rotate(GetIdentityMatrix(), angle, glm::vec3(
				rotation.x / sqrt(1 - rotation.w * rotation.w),
				rotation.y / sqrt(1 - rotation.w * rotation.w),
				rotation.z / sqrt(1 - rotation.w * rotation.w)));
		}
		else { rotationmat = GetIdentityMatrix(); }

		// first rotate then translate
		glm::mat4 transformation = translationmat * rotationmat;

		//translate rotation matrix 1 in the relative y direction to get the relative up direction
		glm::mat4 upmat = glm::translate(rotationmat, glm::vec3(0, 1, 0));
		glm::decompose(upmat, scale, rot, lookat, skew, perspective);
		glm::vec3 up = lookat;

		//transform the complete transformation(rotation + translation) to worldspace by 1 in the relative x direction to get the forward vector
		transformation = glm::translate(transformation, glm::vec3(1, 0, 0));
		glm::decompose(transformation, scale, rot, lookat, skew, perspective);

		return glm::lookAt(m_transform->GetPosition(), lookat, up);;
	}

	//void CameraComponent::LookAt(glm::vec3 lookAt)
	//{
	//	m_lookat = lookAt;
	//}
}
