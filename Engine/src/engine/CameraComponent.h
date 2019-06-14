#pragma once
#include "Component.h"
#include "TransformComponent.h"
namespace engine
{
	class CameraComponent : public Component
	{
		TransformComponent* m_transform;
		float m_fov;
		float m_far;
		float m_near;
		float m_width;
		float m_height;
		bool m_perspective;
		glm::mat4 m_projection;
		glm::mat4 m_view;
		//glm::vec3 m_lookat;

	private:

		CameraComponent(TransformComponent* transform, float fov, float width, float height, float far, float near);
		CameraComponent(float fov, float width, float height, float far, float near);

		CameraComponent(TransformComponent* transform, float width, float height, float far, float near);
		CameraComponent(float width, float height, float far, float near);

	public:

		static CameraComponent* PerspectiveCamera(TransformComponent* transform, const float fov, const float width, const float height, const float far, const float near);
		static CameraComponent* PerspectiveCamera(const float fov, const float width, const float height, const float far, const float near);

		static CameraComponent* OrthographicCamera(TransformComponent* transform, const float width, const float height, const float far, const float near);
		static CameraComponent* OrthographicCamera(const float width, const float height, const float far, const float near);

		~CameraComponent();

		TransformComponent* GetTransform() const;

		float GetFov() const;
		float GetFar() const;
		float GetNear() const;
		float GetWidth() const;
		float GetHeight() const;

		glm::mat4 GetProjection() const;
		glm::mat4 GetView() const;

		//void LookAt(glm::vec3 lookAt);
	};
}

