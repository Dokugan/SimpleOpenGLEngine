#pragma once
#include <string>
#include <vector>
#include "GameObject.h"

namespace engine {
	class Scene
	{
		std::string m_id;
		Camera m_mainCamera = Camera::PerspectiveCamera(Transform(glm::vec3(0.0f)), 45.0f, 1920, 1080, 100.0f, 0.1f);;
		std::vector<GameObject*> m_objects;

	public:
		Scene(std::string id);
		~Scene();

		void  SetCamera(Camera& camera);
		Camera* GetCamera() { return &m_mainCamera; }
		const std::string& GetId() const;
		void AddGameObject(GameObject* obj);

		void RenderScene();
	};
}
