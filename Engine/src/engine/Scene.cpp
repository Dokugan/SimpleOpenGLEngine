#include "Scene.h"
//#include <utility>


namespace engine {
	Scene::Scene(std::string id, float ambientIntensity, glm::vec3 ambientColour) :
		m_id(std::move(id)), m_ambientIntensity(ambientIntensity), m_ambientColour(ambientColour)
	{}


	Scene::~Scene()
		= default;

	void Scene::SetCamera(CameraComponent* camera)
	{
		m_mainCamera = camera;
	}

	const std::string& Scene::GetId() const
	{
		return m_id;
	}

	void Scene::AddGameObject(GameObject* obj)
	{
		m_objects.push_back(obj);
	}

	void Scene::AddLightSource(LightSource* lsrc)
	{
		m_lightSources.push_back(lsrc);
	}

	void Scene::RenderScene()
	{
		for (GameObject* obj : m_objects)
		{
			if (m_mainCamera)
			{
				obj->Render(m_mainCamera, m_ambientIntensity, m_ambientColour);
			}			
		}
	}
}
