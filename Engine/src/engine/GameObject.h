#pragma once
#include <vector>
#include <typeinfo>
#include "Component.h"
#include "Transform.h"
#include "Camera.h"

namespace engine {

	class GameObject
	{
		std::vector<Component*> m_components;

	public:
		GameObject();
		GameObject(Transform* transform);
		~GameObject();

		void AddComponent(Component* component);

		template <typename T>
		T* GetComponent()
		{
			for (unsigned int i = 0; i < m_components.size(); i++)
			{
				try
				{
					Component* c = m_components[i];
					T* comp = dynamic_cast<T*>(c);
					if (comp == nullptr)
					{
						continue;
					}
					return comp;

				}
				catch (std::bad_cast bc)
				{
					std::cerr << "bad_cast caught: " << bc.what() << '\n';
				}
			}
			return nullptr;
		}

		void Render(const Camera& camera);
	};
}