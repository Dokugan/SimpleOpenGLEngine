#include "Scene.h"
#include <iostream>


Scene::Scene(Camera& mainCamera):
	m_mainCamera(mainCamera)
{
}


Scene::~Scene()
= default;

void Scene::AddGameObject(GameObject *obj)
{
	m_game_objects.push_back(obj);
}

void Scene::RenderScene()
{
	for (GameObject* obj : m_game_objects)
	{
		//std::cout << "rendering" << std::endl;
		obj->Render(m_mainCamera);
	}
}
