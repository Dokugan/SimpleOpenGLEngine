#pragma once
#include <string>
#include "Game.h"
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
		typedef void(*update_func)(double deltaTime);
		typedef void(*key_cb_func)(int, int, int, int);
		typedef void(*mouse_cb_func)(int, int, int);

		std::string m_title = "";
		int m_windowWidth;
		int m_windowHeight;
		GLFWwindow* m_window;
		Game* m_game;
		Config* m_config;
		update_func m_update;
		std::thread m_gameThread;
		std::map<int, int> m_key_status;
		std::map<int, int> m_mouse_status;
		double m_delta_time;
		double m_delta_mouse_x, m_delta_mouse_y;

		glm::vec2 inputAxis;

		static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
		static void MouseCallback(GLFWwindow* window, int button, int action, int mods);
		void ComputeInputAxis();

	public:
		bool m_init = false;
		//Time since last frame

		key_cb_func key_callback = nullptr;
		mouse_cb_func mouse_callback = nullptr;

		GameWindow(int windowWidth, int windowHeight, const std::string& title, update_func updateFunc);
		~GameWindow();

		void SetupWindow();
		void SetWindowResizeCallback(void(*cbfunc)(GLFWwindow *, int, int)) const;
		/*!
		 * @param mode one of CURSOR_NORMAL, CURSOR_DISABLED or CURSOR_HIDDEN
		 */
		void SetCursorMode(int mode) const;
		void SetRawMouseInput() const;

		glm::vec2* GetInputAxis();

		int GetDeltaTime();
		void GetDeltaMousePos(double* dx, double* dy) const;
		void GetMousePosition(double* xpos, double* ypos) const;
		int GetMouseButtonState(int mousebtn) const;
		void GetWindowSize(int* width, int* height) const;
		void SetKeyCallback(void(*cb_func)(int key, int scancode, int action, int mods));
		void SetMouseClickCallback(void(*cb_func)(int button, int action, int mods));
		int GetKeyStatus(int key) const;

		Game* GetGame() const { return m_game; };
	private:
		void GameLoop();
	};
}
