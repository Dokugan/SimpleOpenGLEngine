#include "GameObject.h"
#include "components/MeshComponent.h"
#include "components/TransformComponent.h"
#include "Scene.h"

namespace engine {
	GameObject::GameObject()
	{
		m_components.push_back(new TransformComponent());
	}

	GameObject::GameObject(const GameObject& o)
	{
		for (auto c : o.m_components)
			m_components.push_back(c);
	}

	GameObject::GameObject(TransformComponent* transform)
	{
		transform->SetParent(this);
		m_components.push_back(transform);
	}

	GameObject::~GameObject()
		= default;

	void GameObject::AddComponent(Component* component)
	{
		component->SetParent(this);
		m_components.push_back(component);
	}

	void GameObject::Render(const CameraComponent* camera, LightSources* lights, float ambientIntensity, glm::vec3 ambientColour)
	{
		auto mesh = GetComponent<MeshComponent>();
		if (mesh != nullptr)
		{
			mesh->Render(camera, lights, ambientIntensity, ambientColour);
		}
	}
}
