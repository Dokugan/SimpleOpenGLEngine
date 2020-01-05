# Simple OpenGL Engine

A rendering engine which uses OpelGL

## How To Use

The first thing required is a window in which to draw. This can be created by creating a `GameWindow` instance.
The `GameWindow` constructor takes the following arguments:
* A Window Title.
* A function reference to the update function that takes a single int, which is the delta time between frames.
* A window width.
* A window height.
Window width and height are optional parameters, if left blank or 0 they will be retrieved from the engines config file.

```cpp
// dt is the delta time between frames that the engine passes to the update function on each call
void Update(double dt){}

int main()
{
    GameWindow window = new GameWindow("Window Title", Update);
}
```
The engine has a structure of objects that decide where and what is rendered on the screen. At the root is the `GameWindow` class.
A `GameWindow` manages a single `Game` instance. A `Game` has a collection of `Scene`s. Only one `Scene` can be active at a time.
The active `Scene` can be selected by calling `game.SetActiveScene("[name/id of the scene]")` where `game` is the `Game` instance retrieved from the `GameWindow` instance.
Each `Scene` has a collection of `GameObject`s, `LightSource`s and a main `CameraComponent` which is used for rendring the scene.
Each `GameObject` has an `Update(double deltaTime)` function which is called each frame with the time that has elapsed between the last frame and the current one. This way each object can have it's own behaviour. 
A `GameObject` also has a collection of `Component`s which specify further behaviour of a `GameObject` such as a `MeshComponent` that makes it visible in the scene or a `TransformComponent` which manages the position of the object in world space.

The `GameWindow` constructor will create a new `Game` instance. This instance can be retrieved by calling `window.GetGame()`.
New scenes can be added to the game using `game.AddScene("[name/id of the new scene]")`.
Next thing required is a camera that defines how the scene is rendered. A camera can be created by instantiating a `CameraComponent` which can be done by using either the `PerspectiveCamera()` constructor or the `OrthographicCamera()` constructor.
A `CameraComponent` needs at least a `width`, a `height`, a `far` value and a `near` value. Or if it's a perspective camera, it also needs an `fov` as the first argument. Additionally, a `TransformComponent` can be passed as the first parameter to give it a position in world space. If the `TransformComponent` is ommited, one with default values of 0 will be created automatically.
The created camera can then be set as default in the scene by calling `scene.SetCamera(camera)`.

After adding a camera, objects with a `MeshComponent` are needed in order to see anything on the screen.
Once a `GameObject` has been created, A `MeshComponent` can be added by first instantiating one by passing a path to a .obj file in the constructor, after which is can be added to the object by calling the `AddComponent(mesh)` function in which `mesh` is a reference to the created `MeshComponent`.

The created object and it's components can be added to a `Scene` using `AddGameoObject(object)` in which `object` is a reference to the `GameObject` instance.

A simple application that renders one object should look something like this:

```cpp
void Update(double dt){}

int main(int argc, char* argv[])
{
	using namespace engine;
    // Create window and get the Game instance
	GameWindow* window = new GameWindow("TestWindow", Update);
	Game* game = window->GetGame();

    // Add scene to game
	Scene* mainScene = game->AddScene("Mainscene");
	int width = 0, height = 0;

    // Make sure window is initialized
	while (!window->m_init){	
		Sleep(1);
	}

    // Get window size since none was given in constructor
	window->GetWindowSize(&width, &height);

    // Add a new camera to the scene
	Camera* camera = CameraComponent::PerspectiveCamera(new TransformComponent(glm::vec3(.0f, 0.f, .0f)), 70.0f, static_cast<float>(width), static_cast<float>(height), 200.0f, 0.1f);
	mainScene->SetCamera(camera);

    // Add a gameobject with mesh to the scene
	GameObject* obj = new GameObject(new TransformComponent(glm::vec3(3.0f, 0.0f, 0.0f)));
	auto mesh = new MeshComponent("[Path to .obj file]");
	obj->AddComponent(mesh);

    // Add object to scene
	mainScene->AddGameObject(obj);

    // Add a directional light
	mainScene->AddDirectionalLight(DirectionalLight(
		glm::vec3(.5f, -1.f, 0.7f),
		glm::vec3(.6f, .6f, .6f),
		glm::vec3(1.f, 1.f, 1.f)
	));
    
	std::cin.get();
}
```