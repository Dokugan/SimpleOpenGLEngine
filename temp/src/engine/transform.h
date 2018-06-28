#pragma once
#include "component.h"
#include "../vendor/glm/glm.hpp"

class Transform :
	public Component
{
	glm::vec3 m_position;
	glm::vec3 m_rotation;
	float m_scale;

public:
	Transform();
	Transform(glm::vec3 position);
	Transform(glm::vec3 position, glm::vec3 rotation);

	glm::vec3 GetPosition() const;

	void SetScale(float scale);
	void SetRotation(glm::vec3 rotation);

	void Rotate(glm::vec3 rotation);
	void Scale(float scale);
	void Translate(glm::vec3 destination);
};

