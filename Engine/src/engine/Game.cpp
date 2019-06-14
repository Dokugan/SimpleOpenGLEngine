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
			auto objVec = m_activeScene->GetObjects();
			for (auto it = objVec->begin(); it != objVec->end(); ++it)
			{
				GameObject* obj = &(*it);
				obj->Update(deltaTime);
			}
		}
	}

	void Game::RenderScene()
	{
		m_activeScene->RenderScene();
	}
}
