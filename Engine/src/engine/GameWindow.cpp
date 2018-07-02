#include "GameWindow.h"

#include <GLFW/glfw3.h>
#include <thread>

namespace engine {

	GameWindow::GameWindow(const int windowWidth, const int windowHeight, const std::string& title, void(*update_func)()):
	m_windowWidth(windowWidth), m_windowHeight(windowHeight), Update(update_func)
	{
		m_game = new Game();
		m_gameThread = std::thread(&GameWindow::SetupWindow, this);
	}



	GameWindow::~GameWindow()
		= default;

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
		m_init = true;
		GameLoop();
	}

	void GameWindow::SetWindowResizeCallback(void(* cbfunc)(GLFWwindow*, int, int)) const
	{
		glfwSetWindowSizeCallback(m_window, cbfunc);
	}

	void GameWindow::GetWindowSize(int* width, int* height) const
	{
		glfwGetWindowSize(m_window, width, height);
	}

	void GameWindow::SetKeyCallback(void(* key_func)(GLFWwindow*, int, int, int, int)) const
	{
		glfwSetKeyCallback(m_window, key_func);
	}

	void GameWindow::GameLoop()
	{
		while (!glfwWindowShouldClose(m_window))
		{	
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glfwPollEvents();
			Update();
			if (m_game->GetActiveScene())
			{
				m_game->RenderScene();
			}			
			glfwSwapBuffers(m_window);
		}
	}
}
