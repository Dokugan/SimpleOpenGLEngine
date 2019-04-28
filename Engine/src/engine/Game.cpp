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
				m_activeScene = s;
			}
		}
	}

	Scene* Game::AddScene(const std::string& id)
	{
		const auto newScene = new Scene(id);
		m_scenes.push_back(newScene);
		m_activeScene = newScene;
		return newScene;
	}

	Scene* Game::GetActiveScene()
	{
		return m_activeScene;
	}

	void Game::Update(double deltaTime)
	{
		if (m_activeScene)
		{
			for (GameObject* obj : m_activeScene->GetObjects())
			{
				obj->Update(deltaTime);
			}
		}
	}

	void Game::RenderScene()
	{
		m_activeScene->RenderScene();
	}
}
