#include "GameObject.h"
#include "MeshComponent.h"
#include "TransformComponent.h"
#include "Scene.h"

namespace engine {
	GameObject::GameObject()
	{
		const auto transform = new TransformComponent();
		m_components.push_back(transform);
	}

	GameObject::GameObject(TransformComponent* transform)
	{
		transform->SetParent(this);
		m_components.push_back(transform);
	}

	GameObject::~GameObject()
		= default;

	void GameObject::Delete()
	{
		for (auto c : m_components)
			delete c;
	}

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
