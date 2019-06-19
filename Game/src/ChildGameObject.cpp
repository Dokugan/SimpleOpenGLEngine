#include "ChildGameObject.h"
#include "engine/components/TransformComponent.h"

ChildGameObject::ChildGameObject(engine::TransformComponent* transform):
	GameObject(transform)
{
}

void ChildGameObject::Update(double dt)
{
	auto transform = GetComponent<engine::TransformComponent>();
	transform->Rotate(glm::vec3(1, 1, 1), dt);
	transform->Translate(glm::vec3(0,1,0) * static_cast<float>(dt) * static_cast<float>(m_dir));
	if (transform->GetPosition().y >= float(5 * m_dir) && m_dir == 1)
	{
		m_dir = -1;
	}
	if (transform->GetPosition().y <= float(5 * m_dir) && m_dir == -1)
	{
		m_dir = 1;
	}
	// auto transform = GetComponent<engine::TransformComponent>();
	// transform->Translate(glm::vec3(.1f, 0.1f, 0.1f));
	// std::cout << transform->GetPosition().x << ", " 
	// 	<< transform->GetPosition().y << ", " 
	// 	<< transform->GetPosition().z << '\n';
};
