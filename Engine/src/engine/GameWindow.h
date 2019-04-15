#pragma once
#include <string>
#include <thread>
#include "Game.h"
#include "Config.h"

typedef struct GLFWwindow GLFWwindow;

namespace engine {
	// class Game;
	// class Config;

	class GameWindow
	{
		std::string m_title = "";
		int m_windowWidth;
		int m_windowHeight;
		GLFWwindow* m_window;
		Game* m_game;
		Config* m_config;
		void(*Update)();
		std::thread m_gameThread;

		static void(*key_cb_func)(int, int, int, int);
		static void(*mouse_cb_func)(int, int, int);

		//static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
		//static void MouseCallback(GLFWwindow* window, int button, int action, int mods);

	public:
		bool m_init = false;

		GameWindow(int windowWidth, int windowHeight, const std::string& title, void(*updateFunc)());
		~GameWindow();

		void SetupWindow();
		void SetWindowResizeCallback(void(*cbfunc)(GLFWwindow *, int, int)) const;

		int GetMouseButtonState(int mousebtn) const;
		void GetWindowSize(int* width, int* height) const;
		// static void SetKeyCallback(void (*key_func)(GLFWwindow*, int key, int scancode, int action, int mods)) const;
		// static void SetMouseClickCallback(void(*click_func)(GLFWwindow *, int button, int action, int mods)) const;

		Game* GetGame() const { return m_game; };
	private:
		void GameLoop() const;
	};

	enum Mouse
	{
		#define MOUSE_BUTTON_1   0
		#define MOUSE_BUTTON_2   1
		#define MOUSE_BUTTON_3   2
		#define MOUSE_BUTTON_4   3
		#define MOUSE_BUTTON_5   4
		#define MOUSE_BUTTON_6   5
		#define MOUSE_BUTTON_7   6
		#define MOUSE_BUTTON_8   7
		#define MOUSE_BUTTON_LAST   GLFW_MOUSE_BUTTON_8
		#define MOUSE_BUTTON_LEFT   GLFW_MOUSE_BUTTON_1
		#define MOUSE_BUTTON_MIDDLE   GLFW_MOUSE_BUTTON_3
		#define MOUSE_BUTTON_RIGHT   GLFW_MOUSE_BUTTON_2

		#define RELEASE 0
		#define PRESS 1
		#define REPEAT 2
	};
}
