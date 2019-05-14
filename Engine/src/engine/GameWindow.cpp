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

	GameWindow::GameWindow(const std::string& title, update_func updateFunc, const int windowWidth, const int windowHeight) :
		m_update(updateFunc), m_title(title)
	{
		m_game = new Game();
		if (windowWidth == 0)
			m_windowWidth = GetSetting("windowWidth").at(0);
		else
			m_windowWidth = windowWidth;
		if (windowHeight == 0)
			m_windowHeight = GetSetting("windowHeight").at(0);
		else
			m_windowHeight = windowHeight;
		m_inputAxisNegativeX = GetSetting("inputAxisNegativeX");
		m_inputAxisPositiveX = GetSetting("inputAxisPositiveX");
		m_inputAxisNegativeY = GetSetting("inputAxisNegativeY");
		m_inputAxisPositiveY = GetSetting("inputAxisPositiveY");
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
			else gameWindow->m_key_status.insert(std::pair<int, int>(key, action));

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
			gameWindow->m_mouse_status.insert(std::pair<int, int>(button, action));

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
		for (int i : m_inputAxisPositiveY)
		{
			auto it = m_key_status.find(i);
			if (it != end && it->second != ACTION_RELEASE)
			{
				inputvec += glm::vec2(0.0f, 1.0f);
				break;
			}
		}
		for (int i : m_inputAxisNegativeY)
		{
			auto it = m_key_status.find(i);
			if (it != end && it->second != ACTION_RELEASE)
			{
				inputvec += glm::vec2(0.0f, -1.0f);
				break;
			}
		}
		for (int i : m_inputAxisPositiveX)
		{
			auto it = m_key_status.find(i);
			if (it != end && it->second != ACTION_RELEASE)
			{
				inputvec += glm::vec2(1.0f, 0.0f);
				break;
			}
		}
		for (int i : m_inputAxisNegativeX)
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
		// int major;
		// int minor;
		// int rev;
		// glfwGetVersion(&major, &minor, &rev);
		// printf("GLFW version: %d.%d.%d \n", major, minor, rev);

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

	void GameWindow::SetWindowResizeCallback(void(*cbfunc)(GLFWwindow*, int, int)) const
	{
		glfwSetWindowSizeCallback(m_window, cbfunc);
	}

	void GameWindow::SetCursorMode(int mode) const
	{
		glfwSetInputMode(m_window, GLFW_CURSOR, mode);
	}

	void GameWindow::SetRawMouseInput() const
	{
		if (glfwRawMouseMotionSupported())
		{
			if (glfwGetInputMode(m_window, GLFW_CURSOR) != GLFW_CURSOR_DISABLED)
			{
				glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			}
			glfwSetInputMode(m_window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
		}
	}

	glm::vec2* GameWindow::GetInputAxis()
	{
		return &inputAxis;
	}

	void GameWindow::GetDeltaMousePos(double* dx, double* dy) const
	{
		*dx = m_delta_mouse_x;
		*dy = m_delta_mouse_y;
	}

	void GameWindow::GetMousePosition(double* xpos, double* ypos) const
	{
		glfwGetCursorPos(m_window, xpos, ypos);
	}

	int GameWindow::GetMouseButtonState(int mousebtn) const
	{
		return glfwGetMouseButton(m_window, mousebtn);
	}

	void GameWindow::GetWindowSize(int* width, int* height) const
	{
		glfwGetWindowSize(m_window, width, height);
	}

	void GameWindow::SetKeyCallback(void(*cb_func)(int key, int scancode, int action, int mods))
	{
		key_callback = cb_func;
	}

	void GameWindow::SetMouseClickCallback(void(*cb_func)(int button, int action, int mods))
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
		auto time = std::chrono::high_resolution_clock::now();
		double mousex, mousey;
		glfwGetCursorPos(m_window, &mousex, &mousey);

		while (!glfwWindowShouldClose(m_window))
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			double newMousex, newMousey;
			glfwGetCursorPos(m_window, &newMousex, &newMousey);
			m_delta_mouse_x = newMousex - mousex;
			m_delta_mouse_y = newMousey - mousey;
			mousex = newMousex;
			mousey = newMousey;

			std::chrono::duration<double> dtime = std::chrono::high_resolution_clock::now() - time;
			time = std::chrono::high_resolution_clock::now();
			m_delta_time = dtime.count();
			m_update(m_delta_time);
			m_game->Update(m_delta_time);
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
