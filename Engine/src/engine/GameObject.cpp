#include "GameObject.h"
#include "MeshComponent.h"


namespace engine {
	GameObject::GameObject()
	{
		auto transform = new TransformComponent();
		m_components.push_back(transform);
	}

	GameObject::GameObject(TransformComponent* transform)
	{
		m_components.push_back(transform);
	}

	GameObject::~GameObject()
	{
		for (auto c : m_components)
		{
			delete c;
		}
	}

	void GameObject::AddComponent(Component* component)
	{
		m_components.push_back(component);
	}

	void GameObject::Render(const CameraComponent* camera, float ambientIntensity, glm::vec3 ambientColour)
	{
		auto mesh = GetComponent<MeshComponent>();
		if (mesh != nullptr)
		{
			mesh->Render(camera, this, ambientIntensity, ambientColour);
		}
	}
}
