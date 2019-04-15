#pragma once
#include "TransformComponent.h"

namespace engine
{
	class CameraComponent : public Component
	{
		TransformComponent m_transform;
		float m_fov;
		float m_far;
		float m_near;
		float m_width;
		float m_height;
		bool m_perspective;
		glm::mat4 m_projection;
		glm::mat4 m_view;

	private:

		CameraComponent(const TransformComponent& transform, float fov, float width, float height, float far, float near);
		CameraComponent(float fov, float width, float height, float far, float near);

		CameraComponent(const TransformComponent& transform, float width, float height, float far, float near);
		CameraComponent(float width, float height, float far, float near);

	public:

		static CameraComponent PerspectiveCamera(const TransformComponent& transform, const float fov, const float width, const float height, const float far, const float near)
		{
			return CameraComponent(transform, fov, width, height, far, near);
		}
		static CameraComponent PerspectiveCamera(const float fov, const float width, const float height, const float far, const float near)
		{
			return CameraComponent(fov, width, height, far, near);
		}

		static CameraComponent OrthographicCamera(const TransformComponent& transform, const float width, const float height, const float far, const float near)
		{
			return CameraComponent(transform, width, height, far, near);
		}
		static CameraComponent OrthographicCamera(const float width, const float height, const float far, const float near)
		{
			return CameraComponent(width, height, far, near);
		}

		~CameraComponent();

		TransformComponent& GetTransform();
		glm::mat4 GetProjection() const;
		glm::mat4 GetView() const;

		void LookAt(glm::vec3 lookAt);
	};
}

