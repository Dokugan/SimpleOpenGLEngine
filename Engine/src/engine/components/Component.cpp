#include "Component.h"
#include "../GameObject.h"

namespace engine {
	
	Component::Component()
		= default;

	Component::Component(const Component& o)
	{
		m_parent = o.m_parent;
	}

	Component::~Component()
		= default;

	void Component::SetParent(GameObject* parent)
	{
		m_parent = parent;
	}
}