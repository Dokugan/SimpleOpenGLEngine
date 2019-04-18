#include "engine/GameWindow.h"
#include "engine/MeshComponent.h"
#include <windows.h>
#include <iostream>

engine::GameWindow* window;

void Update()
{
	glm::vec2* i = window->GetInputAxis();
	std::cout << i->x << ", " << i->y << '\n';
}

void KeyboardEvent(int key, int scancode, int action, int mods)
{
	std::cout << key;
}

int main(int argc, char* argv[])
{
	using namespace engine;
	window = new GameWindow(1920, 1080, "TestWindow", Update);
	Game* game = window->GetGame();
	Scene* mainScene = game->AddScene("Mainscene");
	int width = 0, height = 0;
	while (!window->m_init)
	{	
		Sleep(1);
	}
	window->GetWindowSize(&width, &height);
	CameraComponent camera = CameraComponent::PerspectiveCamera(TransformComponent(glm::vec3(-5.0f, 5.0f, 5.0f)), 45.0f, static_cast<float>(width), static_cast<float>(height), 200.0f, 0.1f);
	mainScene->SetCamera(camera);
	GameObject* obj = new GameObject();
	obj->AddComponent(new MeshComponent("res/models/texturedcube.obj"));
	mainScene->AddGameObject(obj);
	//window->SetKeyCallback(&KeyboardEvent);
	std::cin.get();
}
