#include "engine/GameWindow.h"
#include "engine/MeshComponent.h"
#include <windows.h>
#include <iostream>

void Update()
{
	
}

int main(int argc, char* argv[])
{
	using namespace engine;
	GameWindow* window = new GameWindow(1920, 1080, "TestWindow", Update);
	Game* game = window->GetGame();
	Scene* mainScene = game->AddScene("Mainscene");
	int width = 0, height = 0;
	while (!window->m_init)
	{	
		Sleep(1);
	}
	window->GetWindowSize(&width, &height);
	Camera camera = Camera::PerspectiveCamera(Transform(glm::vec3(-5.0f, 5.0f, 5.0f)), 45.0f, static_cast<float>(width), static_cast<float>(height), 200.0f, 0.1f);
	mainScene->SetCamera(camera);
	GameObject* obj = new GameObject();
	obj->AddComponent(new MeshComponent("res/models/texturedcube.obj"));
	mainScene->AddGameObject(obj);
	std::cin.get();
}
