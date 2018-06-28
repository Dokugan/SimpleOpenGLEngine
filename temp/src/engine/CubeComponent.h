#pragma once
#include "component.h"
class GameObject;
class Camera;

class CubeComponent :
	public Component
{

public:
	CubeComponent();

	void Render(const Camera& camera, GameObject* obj) const;
};

