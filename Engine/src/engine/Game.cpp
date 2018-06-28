#include "Game.h"



namespace engine {
	Game::Game()
	{
	}

	Game::~Game()
	{
		for (auto s : m_scenes)
		{
			delete s;
		}
	}

	void Game::SetActiveScene(const std::string& id)
	{
		for (auto s : m_scenes)
		{
			if (s->GetId() == id)
			{
				m_avtiveScene = s;
			}
		}
	}

	Scene* Game::AddScene(const std::string& id)
	{
		const auto newScene = new Scene(id);
		m_scenes.push_back(newScene);
		m_avtiveScene = newScene;
		return newScene;
	}

	Scene* Game::GetActiveScene()
	{
		return m_avtiveScene;
	}

	void Game::RenderScene()
	{
		m_avtiveScene->RenderScene();
	}
}
