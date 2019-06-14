#pragma once
#include <vector>
#include <typeinfo>
#include <iostream>
#include "../ext/glm/glm.hpp"

namespace engine {

	struct LightSources;
	class LightSource;
	class Component;
	class TransformComponent;
	class CameraComponent;

	class GameObject
	{
		std::vector<Component*> m_components;

	public:
		GameObject();
		GameObject(TransformComponent* transform);
		virtual ~GameObject();

		virtual void Update(double deltaTime){}

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
					return *(&comp);

				}
				catch (std::bad_cast bc)
				{
					std::cerr << "bad_cast caught: " << bc.what() << '\n';
				}
			}
			return nullptr;
		}

		void Render(const CameraComponent* camera, LightSources* lights, float ambientIntensity, glm::vec3 ambientColour);
	};
}
