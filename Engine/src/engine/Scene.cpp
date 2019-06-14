#include "Scene.h"
#include "DirectionalLight.h"

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

	CameraComponent* Scene::GetCamera() const
	{
		return m_mainCamera;
	}

	std::vector<GameObject>* Scene::GetObjects()
	{
		return &m_objects;
	}

	const std::string& Scene::GetId() const
	{
		return m_id;
	}

	void Scene::AddGameObject(const GameObject& obj)
	{
		m_objects.push_back(obj);
	}

	void Scene::AddDirectionalLight(const DirectionalLight& lsrc)
	{
		m_lightSources.directionalLights.push_back(lsrc);
	}

	void Scene::RenderScene()
	{
		for (GameObject& obj : m_objects)
		{
			if (m_mainCamera)
			{
				obj.Render(m_mainCamera, &m_lightSources, m_ambientIntensity, m_ambientColour);
			}			
		}
	}
}
