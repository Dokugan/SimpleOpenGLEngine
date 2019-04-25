#pragma once
#include <string>
#include <vector>
#include "GameObject.h"
#include "LightSource.h"

namespace engine {
	class Scene
	{
		std::string m_id;
		CameraComponent* m_mainCamera;
		std::vector<GameObject*> m_objects;
		std::vector<LightSource*> m_lightSources;

	public:
		Scene(std::string id);
		~Scene();

		void  SetCamera(CameraComponent* camera);
		CameraComponent* GetCamera() { return m_mainCamera; }
		const std::string& GetId() const;
		void AddGameObject(GameObject* obj);
		void AddLightSource(LightSource* lsrc);
		std::vector<GameObject*> GetObjects() { return m_objects; }

		void RenderScene();
	};
}
