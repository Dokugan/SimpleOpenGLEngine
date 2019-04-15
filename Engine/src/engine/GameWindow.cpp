#include "GameWindow.h"
#if !defined(__gl_h_) && !defined(__GL_H__) && !defined(_GL_H) && !defined(__X_GL_H)
#include <GL/glew.h>
#endif
#include <GLFW/glfw3.h>
#include "Game.h"
#include "Config.h"

namespace engine {

	GameWindow::GameWindow(const int windowWidth, const int windowHeight, const std::string& title, void(*update_func)()):
	m_windowWidth(windowWidth), m_windowHeight(windowHeight), Update(update_func)
	{
		m_game = new Game();
		m_config = new Config();
		m_gameThread = std::thread(&GameWindow::SetupWindow, this);
	}

	GameWindow::~GameWindow()
		= default;

	// void GameWindow::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
	// {
	// 	key_cb_func(key, scancode, action, mods);
	// }

	// void GameWindow::MouseCallback(GLFWwindow* window, int button, int action, int mods)
	// {
	// 	mouse_cb_func(button, action, mods);
	// }

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
		//glfwSetKeyCallback(m_window, this->KeyCallback);
		//glfwSetMouseButtonCallback(m_window, MouseCallback);
		m_init = true;
		GameLoop();
	}

	void GameWindow::SetWindowResizeCallback(void(* cbfunc)(GLFWwindow*, int, int)) const
	{
		glfwSetWindowSizeCallback(m_window, cbfunc);
	}

	int GameWindow::GetMouseButtonState(int mousebtn) const
	{
		return glfwGetMouseButton(m_window, mousebtn);
	}

	void GameWindow::GetWindowSize(int* width, int* height) const
	{
		glfwGetWindowSize(m_window, width, height);
	}

	// void GameWindow::SetKeyCallback(void(* key_func)(int key, int scancode, int action, int mods)) const
	// {
	// 	key_cb_func = key_func;
	// }

	// void GameWindow::SetMouseClickCallback(void(* click_func)(GLFWwindow*, int button, int action, int mods)) const
	// {
	// 	glfwSetMouseButtonCallback(m_window, click_func);
	// }

	void GameWindow::GameLoop() const
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
			glfwPollEvents();
		}
	}
}
