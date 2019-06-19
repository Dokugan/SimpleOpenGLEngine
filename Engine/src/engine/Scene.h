#pragma once
#include <string>
#include <vector>
#include "GameObject.h"
#include "LightSource.h"

namespace engine {

	class DirectionalLight;
	class CameraComponent;
	class GameObject;

	class Scene
	{
		std::string m_id;
		CameraComponent* m_mainCamera;
		std::vector<GameObject*> m_objects;
		LightSources m_lightSources;
		float m_ambientIntensity;
		glm::vec3 m_ambientColour;


	public:
		Scene(std::string id, float ambientIntensity = 0.2, glm::vec3 ambientColour = glm::vec3(1));
		~Scene();

		void  SetCamera(CameraComponent* camera);
		CameraComponent* GetCamera() const;
		const std::string& GetId() const;
		void AddGameObject(GameObject* obj);
		void AddDirectionalLight(const DirectionalLight& lsrc);
		std::vector<GameObject*>* GetObjects();

		void RenderScene();
		void Update(double deltaTime);
	};

}
