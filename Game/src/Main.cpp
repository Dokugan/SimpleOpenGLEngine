#include "engine/GameWindow.h"
#include "engine/MeshComponent.h"
#include <windows.h>
#include <iostream>
#include "ChildGameObject.h"

engine::GameWindow* window;
engine::CameraComponent* camera;

void Update()
{
	if (camera)
	{
		camera->GetTransform()->Translate(glm::vec3(-.1f, -0.1f, 0.1f));
	}
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
	camera = CameraComponent::PerspectiveCamera(new TransformComponent(glm::vec3(.0f, .0f, .0f)), 45.0f, static_cast<float>(width), static_cast<float>(height), 200.0f, 0.1f);
	mainScene->SetCamera(camera);
	GameObject* obj = new GameObject(new TransformComponent(glm::vec3(5.0f, 0.0f, 0.0f)));
	camera->LookAt(obj->GetComponent<TransformComponent>()->GetPosition());
	obj->AddComponent(new MeshComponent("res/models/texturedcube.obj"));
	mainScene->AddGameObject(obj);
	//window->SetKeyCallback(&KeyboardEvent);
	std::cin.get();
}
