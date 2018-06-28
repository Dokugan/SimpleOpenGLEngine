#pragma once
#include "Transform.h"

namespace engine
{
	class Camera
	{
		Transform m_transform;
		float m_fov;
		float m_far;
		float m_near;
		float m_width;
		float m_height;
		bool m_perspective;
		glm::mat4 m_projection;
		glm::mat4 m_view;

	private:

		Camera(const Transform& transform, float fov, float width, float height, float far, float near);
		Camera(float fov, float width, float height, float far, float near);

		Camera(const Transform& transform, float width, float height, float far, float near);
		Camera(float width, float height, float far, float near);

	public:

		static Camera PerspectiveCamera(const Transform& transform, const float fov, const float width, const float height, const float far, const float near)
		{
			return Camera(transform, fov, width, height, far, near);
		}
		static Camera PerspectiveCamera(const float fov, const float width, const float height, const float far, const float near)
		{
			return Camera(fov, width, height, far, near);
		}

		static Camera OrthographicCamera(const Transform& transform, const float width, const float height, const float far, const float near)
		{
			return Camera(transform, width, height, far, near);
		}
		static Camera OrthographicCamera(const float width, const float height, const float far, const float near)
		{
			return Camera(width, height, far, near);
		}

		~Camera();

		Transform& GetTransform();
		glm::mat4 GetProjection() const;
		glm::mat4 GetView() const;

		void LookAt(glm::vec3 lookAt);
	};
}

