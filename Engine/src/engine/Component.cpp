#include "Component.h"
#include "GameObject.h"

namespace engine {
	
	Component::Component()
	{
	}

	Component::~Component()
	{
	}
	void Component::SetParent(GameObject* parent)
	{
		m_parent = parent;
	}
}