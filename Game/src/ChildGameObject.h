#pragma once
#include "engine/GameObject.h"

class ChildGameObject : public engine::GameObject
{
public:
	void Update(double dt) override;
	
};
