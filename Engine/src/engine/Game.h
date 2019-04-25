#pragma once
#include <string>
#include <vector>
#include "Scene.h"

namespace engine {
	class Game
	{
		std::vector<Scene*> m_scenes;
		Scene* m_activeScene = nullptr;

	public:
		Game();
		~Game();

		void SetActiveScene(const std::string& id);
		Scene* AddScene(const std::string& id);
		Scene* GetActiveScene();

		void Update();
		void RenderScene();
	};
}
