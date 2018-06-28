#include "GameObject.h"
#include "MeshComponent.h"


namespace engine {
	GameObject::GameObject()
	{
		Transform* transform = new Transform();
		m_components.push_back(transform);
	}

	GameObject::GameObject(Transform* transform)
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

	void GameObject::Render(const Camera& camera)
	{
		MeshComponent* mesh = GetComponent<MeshComponent>();
		if (mesh != nullptr)
		{
			mesh->Render(camera, this);
		}
	}
}
