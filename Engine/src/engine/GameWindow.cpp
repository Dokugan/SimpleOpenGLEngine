#include "GameWindow.h"
#if !defined(__gl_h_) && !defined(__GL_H__) && !defined(_GL_H) && !defined(__X_GL_H)
#include <GL/glew.h>
#endif
#include <GLFW/glfw3.h>
#include "Game.h"
#include "Config.h"
#include <utility>
#include "Input.h"

namespace engine {

	static std::map<GLFWwindow*, GameWindow*> window_map;

	GameWindow::GameWindow(const int windowWidth, const int windowHeight, const std::string& title, void(*update_func)()):
	m_windowWidth(windowWidth), m_windowHeight(windowHeight), Update(update_func)
	{
		m_game = new Game();
		m_config = new Config();
		m_gameThread = std::thread(&GameWindow::SetupWindow, this);
	}

	GameWindow::~GameWindow()
		= default;

	 void GameWindow::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
	 {
		 auto it = window_map.find(window);
		 if (it != window_map.end())
		 {
			 GameWindow* gameWindow = it->second;
			 // std::cout << action;
			 auto it2 = gameWindow->m_key_status.find(key);
			 if (it2 != gameWindow->m_key_status.end())
			 {
				 it2->second = action;
			 }
			 else gameWindow->m_key_status.insert(std::pair<int,int>(key, action));

			 if (gameWindow->key_callback != nullptr)
			 {
				 gameWindow->key_callback(key, scancode, action, mods);
			 }
		 }
	 }

	 void GameWindow::MouseCallback(GLFWwindow* window, int button, int action, int mods)
	 {
		 auto it = window_map.find(window);
		 if (it != window_map.end())
		 {
			 GameWindow* gameWindow = it->second;
			 gameWindow->m_mouse_status.insert(std::pair<int,int>(button, action));

			 if (gameWindow->mouse_callback != nullptr)
			 {
				 gameWindow->mouse_callback(button, action, mods);
			 }
		 }
	 }

	void GameWindow::ComputeInputAxis()
	{
		glm::vec2 inputvec(0);
		const auto end = m_key_status.end();
		for (int i : m_config->AxisYPositive)
		{
			auto it = m_key_status.find(i);
			if (it != end && it->second != ACTION_RELEASE)
			{
				inputvec += glm::vec2(0.0f, 1.0f);
				break;
			}
		}
		for (int i : m_config->AxisYNegative)
		{
			auto it = m_key_status.find(i);
			if (it != end && it->second != ACTION_RELEASE)
			{
				inputvec += glm::vec2(0.0f, -1.0f);
				break;
			}
		}
		for (int i : m_config->AxisXPositive)
		{
			auto it = m_key_status.find(i);
			if (it != end && it->second != ACTION_RELEASE)
			{
				inputvec += glm::vec2(1.0f, 0.0f);
				break;
			}
		}
		for (int i : m_config->AxisXNegative)
		{
			auto it = m_key_status.find(i);
			if (it != end && it->second != ACTION_RELEASE)
			{
				inputvec += glm::vec2(-1.0f, 0.0f);
				break;
			}
		}

		inputAxis = inputvec;
	}

	void GameWindow::SetupWindow()
	{

		if (!glfwInit())
			return;

		m_window = glfwCreateWindow(m_windowWidth, m_windowHeight, m_title.c_str(), nullptr, nullptr);
		if (!m_window)
		{
			glfwTerminate();
			return;
		}
		glfwMakeContextCurrent(m_window);
		glewInit();
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);
		key_callback = nullptr;
		mouse_callback = nullptr;
		glfwSetKeyCallback(m_window, KeyCallback);
		glfwSetMouseButtonCallback(m_window, MouseCallback);
		window_map.insert(std::pair<GLFWwindow*, GameWindow*>(m_window, this));
		m_init = true;
		GameLoop();
	}

	void GameWindow::SetWindowResizeCallback(void(* cbfunc)(GLFWwindow*, int, int)) const
	{
		glfwSetWindowSizeCallback(m_window, cbfunc);
	}

	glm::vec2* GameWindow::GetInputAxis()
	{
		return &inputAxis;
	}

	int GameWindow::GetMouseButtonState(int mousebtn) const
	{
		return glfwGetMouseButton(m_window, mousebtn);
	}

	void GameWindow::GetWindowSize(int* width, int* height) const
	{
		glfwGetWindowSize(m_window, width, height);
	}

	 void GameWindow::SetKeyCallback(void(* cb_func)(int key, int scancode, int action, int mods))
	 {
	 	key_callback = cb_func;
	 }

	 void GameWindow::SetMouseClickCallback(void(* cb_func)(int button, int action, int mods))
	 {
		 mouse_callback = cb_func;
	 }

	int GameWindow::GetKeyStatus(int key) const
	{
		auto it = m_key_status.find(key);
		if (it != m_key_status.end())
		{
			return it->second;
		}
		return 0;
	}

	void GameWindow::GameLoop()
	{
		while (!glfwWindowShouldClose(m_window))
		{	
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			Update();
			if (m_game->GetActiveScene())
			{
				m_game->RenderScene();
			}			
			glfwSwapBuffers(m_window);
			//m_key_status.clear();
			ComputeInputAxis();
			glfwPollEvents();
		}
	}
}
