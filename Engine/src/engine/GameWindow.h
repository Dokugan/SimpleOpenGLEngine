#pragma once
#include <string>
#include <thread>
#include "Game.h"
#include "Config.h"
#include <map>

typedef struct GLFWwindow GLFWwindow;

namespace engine {
	// class Game;
	// class Config;
	typedef struct
	{
		int key;
		int scancode;
		int action;
		int mods;
	} KeyEvent;

	// typedef struct
	// {
	// 	int button;
	// 	int 
	// } MouseButtonEvent;

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
		std::map<int, int> m_key_status;
		std::map<int, int> m_mouse_status;

		glm::vec2 inputAxis;

		static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
		static void MouseCallback(GLFWwindow* window, int button, int action, int mods);
		void ComputeInputAxis();

	public:
		bool m_init = false;

		typedef void(*key_cb_func)(int, int, int, int);
		typedef void(*mouse_cb_func)(int, int, int);
		key_cb_func key_callback = nullptr;
		mouse_cb_func mouse_callback = nullptr;

		GameWindow(int windowWidth, int windowHeight, const std::string& title, void(*updateFunc)());
		~GameWindow();

		void SetupWindow();
		void SetWindowResizeCallback(void(*cbfunc)(GLFWwindow *, int, int)) const;

		glm::vec2* GetInputAxis();

		int GetMouseButtonState(int mousebtn) const;
		void GetWindowSize(int* width, int* height) const;
		void SetKeyCallback(void (*cb_func)(int key, int scancode, int action, int mods));
		void SetMouseClickCallback(void(*cb_func)(int button, int action, int mods));
		int GetKeyStatus(int key) const;

		Game* GetGame() const { return m_game; };
	private:
		void GameLoop();
	};
}
