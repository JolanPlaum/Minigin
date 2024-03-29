#include "SceneManager.h"
#include "Scene.h"

void dae::SceneManager::Init()
{
	for (auto& scene : m_scenes)
	{
		scene->Init();
	}
}

void dae::SceneManager::UpdateGui()
{
	for (auto& scene : m_scenes)
	{
		scene->UpdateGui();
	}
}

void dae::SceneManager::Update()
{
	for (auto& scene : m_scenes)
	{
		scene->Update();
	}
}

void dae::SceneManager::Render() const
{
	for (const auto& scene : m_scenes)
	{
		scene->Render();
	}
}

void dae::SceneManager::Cleanup()
{
	for (auto& scene : m_scenes)
	{
		scene->Cleanup();
	}
}

dae::Scene& dae::SceneManager::CreateScene(const std::string& name)
{
	const auto& scene = std::shared_ptr<Scene>(new Scene(name));
	m_scenes.push_back(scene);
	return *scene;
}
