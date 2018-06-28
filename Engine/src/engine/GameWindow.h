#pragma once
#include <string>
#include <vector>
#include <gl/glew.h>
#include <GLFW/glfw3.h>
#include "Game.h"
#include <thread>


namespace engine {
	class GameWindow
	{
		std::string m_title = "";
		int m_windowWidth, m_windowHeight;
		GLFWwindow* m_window;
		Game* m_game;
		void(*Update)();
		std::thread m_gameThread;

	public:
		bool m_init = false;

		GameWindow(const int windowWidth, const int windowHeight, const std::string& title, void(*updateFunc)());
		~GameWindow();

		void SetupWindow();
		void SetWindowResizeCallback(void(*cbfunc)(GLFWwindow *, int, int)) const;

		void GetWindowSize(int* width, int* height) const;
		void SetKeyCallback(void (*key_func)(GLFWwindow*, int, int, int, int)) const;
		Game* GetGame() const { return m_game; };
	private:
		void GameLoop();
	};
}
