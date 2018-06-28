#pragma once
#include <vector>
#include "gameobject.h"
#include "Camera.h"

class Scene
{
	std::vector<GameObject*> m_game_objects;
	Camera m_mainCamera = Camera::PerspectiveCamera(70.0f, 500.0f, 400.0f, 100.0f, .1f);


public:
	Scene(){}
	Scene(Camera& mainCamera);
	~Scene();

	void AddGameObject(GameObject* obj);
	void RenderScene();

	Camera& GetMainCamera() { return m_mainCamera; }
};
