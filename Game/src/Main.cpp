#include "engine/GameWindow.h"
#include "engine/MeshComponent.h"
#include <windows.h>
#include <iostream>
#include "ChildGameObject.h"
#include "engine/Input.h"
#include "engine/CameraComponent.h"
#include "engine/DirectionalLight.h"

engine::GameWindow* window;
engine::CameraComponent* camera;

void Update(double dt)
{
	 double x, y;
	// window->GetMousePosition(&x, &y);
	// std::cout << x << ", " << y << '\n';
	//std::cout << dt << '\n';
	 window->GetDeltaMousePos(&x, &y);
	//std::cout << x << ", " << y << '\n';
	if (camera)
	{
		if (window->GetKeyStatus(KEY_SPACE))
		{
			camera->GetTransform()->Translate(glm::vec3(0, 1, 0) * static_cast<float>(dt));
		}
		if (window->GetKeyStatus(KEY_LEFT_CONTROL))
		{
			camera->GetTransform()->Translate(glm::vec3(0, -1, 0) * static_cast<float>(dt));
		}
		if (window->GetKeyStatus(KEY_D))
		{
			camera->GetTransform()->Translate(glm::vec3(0, 0, 1) * static_cast<float>(dt));
		}
		if (window->GetKeyStatus(KEY_A))
		{
			camera->GetTransform()->Translate(glm::vec3(0, 0, -1) * static_cast<float>(dt));
		}
		if (window->GetKeyStatus(KEY_W))
		{
			camera->GetTransform()->Translate(glm::vec3(1, 0, 0) * static_cast<float>(dt));
		}
		if (window->GetKeyStatus(KEY_S))
		{
			camera->GetTransform()->Translate(glm::vec3(-1, 0, 0) * static_cast<float>(dt));
		}
		camera->GetTransform()->RotateEuler(glm::vec3(0, x*.5 * dt, y*.5 * dt));
	}
}

void KeyboardEvent(int key, int scancode, int action, int mods)
{
	std::cout << key;
}

int main(int argc, char* argv[])
{
	using namespace engine;
	window = new GameWindow("TestWindow", Update);
	Game* game = window->GetGame();
	Scene* mainScene = game->AddScene("Mainscene");
	int width = 0, height = 0;
	while (!window->m_init)
	{	
		Sleep(1);
	}
	window->GetWindowSize(&width, &height);
	camera = CameraComponent::PerspectiveCamera(new TransformComponent(glm::vec3(.0f, 0.f, .0f)), 45.0f, static_cast<float>(width), static_cast<float>(height), 200.0f, 0.1f);
	mainScene->SetCamera(camera);
	GameObject obj = GameObject(new TransformComponent(glm::vec3(5.0f, 0.0f, 0.0f)));
	auto mesh = new MeshComponent("res/models/baguette.obj");
	obj.AddComponent(mesh);
	mainScene->AddGameObject(obj);
	mainScene->AddDirectionalLight(DirectionalLight(
		glm::vec3(.5f, -1.f, 0.7f),
		glm::vec3(.6f, .6f, .6f),
		glm::vec3(1.f, 1.f, 1.f)
	));
	//window->SetCursorMode(CURSOR_DISABLED);
	window->SetRawMouseInput();
	std::cin.get();
}
