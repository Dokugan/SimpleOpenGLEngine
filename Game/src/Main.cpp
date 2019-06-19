#include "engine/GameWindow.h"
#include "engine/components/MeshComponent.h"
#include <windows.h>
#include <iostream>
#include "ChildGameObject.h"
#include "engine/Input.h"
#include "engine/components/CameraComponent.h"
#include "engine/DirectionalLight.h"

engine::GameWindow* window;
engine::CameraComponent* camera;

glm::vec3 rot;

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
			camera->GetTransform()->Translate(camera->GetTransform()->Right() * static_cast<float>(dt));
		}
		if (window->GetKeyStatus(KEY_A))
		{
			camera->GetTransform()->Translate(-camera->GetTransform()->Right() * static_cast<float>(dt));
		}
		if (window->GetKeyStatus(KEY_W))
		{
			camera->GetTransform()->Translate(camera->GetTransform()->Forward() * static_cast<float>(dt));
		}
		if (window->GetKeyStatus(KEY_S))
		{
			camera->GetTransform()->Translate(-camera->GetTransform()->Forward() * static_cast<float>(dt));
		}

		camera->GetTransform()->Rotate( 0.1f * x * dt, 0.1f * y * dt,   0.0 );
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
	camera = CameraComponent::PerspectiveCamera(new TransformComponent(glm::vec3(.0f, 0.f, .0f)), 70.0f, static_cast<float>(width), static_cast<float>(height), 200.0f, 0.1f);
	mainScene->SetCamera(camera);

	GameObject obj = GameObject(new TransformComponent(glm::vec3(2.0f, 0.0f, 0.0f)));
	auto mesh = new MeshComponent("res/models/baguette.obj");
	obj.AddComponent(mesh);

	GameObject obj2 = GameObject(new TransformComponent(glm::vec3(0.0f, 2.0f, 0.0f)));
	auto mesh2 = new MeshComponent("res/models/baguette.obj");
	obj2.AddComponent(mesh2);

	GameObject obj3 = GameObject(new TransformComponent(glm::vec3(-2.0f, 0.0f, 0.0f)));
	auto mesh3 = new MeshComponent("res/models/baguette.obj");
	obj3.AddComponent(mesh3);

	GameObject obj4 = GameObject(new TransformComponent(glm::vec3(0.0f, -2.0f, 0.0f)));
	auto mesh4 = new MeshComponent("res/models/baguette.obj");
	obj4.AddComponent(mesh4);

	GameObject obj5 = GameObject(new TransformComponent(glm::vec3(0.0f, 0.0f, 2.0f)));
	auto mesh5 = new MeshComponent("res/models/baguette.obj");
	obj5.AddComponent(mesh5);

	GameObject obj6 = GameObject(new TransformComponent(glm::vec3(0.0f, 0.0f, -2.0f)));
	auto mesh6 = new MeshComponent("res/models/baguette.obj");
	obj6.AddComponent(mesh6);


	mainScene->AddGameObject(obj);
	mainScene->AddGameObject(obj2);
	mainScene->AddGameObject(obj4);
	mainScene->AddGameObject(obj5);
	mainScene->AddGameObject(obj6);

	mainScene->AddDirectionalLight(DirectionalLight(
		glm::vec3(.5f, -1.f, 0.7f),
		glm::vec3(.6f, .6f, .6f),
		glm::vec3(1.f, 1.f, 1.f)
	));
	//window->SetCursorMode(CURSOR_DISABLED);
	window->SetRawMouseInput();
	std::cin.get();
}
