#pragma once
#include "engine/GameObject.h"

class ChildGameObject : public engine::GameObject
{

	int m_dir = 1;
public:
	ChildGameObject(engine::TransformComponent* transform);

	void Update(double dt) override;
};
