#pragma once
#include <string>
#include <vector>
#include "GameObject.h"
#include "LightSource.h"

namespace engine {
	class Scene
	{
		std::string m_id;
		CameraComponent m_mainCamera = CameraComponent::PerspectiveCamera(TransformComponent(glm::vec3(0.0f)), 45.0f, 1920, 1080, 100.0f, 0.1f);;
		std::vector<GameObject*> m_objects;
		std::vector<LightSource*> m_lightSources;

	public:
		Scene(std::string id);
		~Scene();

		void  SetCamera(CameraComponent& camera);
		CameraComponent* GetCamera() { return &m_mainCamera; }
		const std::string& GetId() const;
		void AddGameObject(GameObject* obj);
		void AddLightSource(LightSource* lsrc);

		void RenderScene();
	};
}
