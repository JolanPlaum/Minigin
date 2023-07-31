//-----------------------------------------------------------------
// Includes
//-----------------------------------------------------------------
#include "Scene.h"
#include "GameObject.h"
#include "Component.h"
#include <iostream>

using namespace dae;

unsigned int Scene::m_IdCounter = 0;


//-----------------------------------------------------------------
// Constructors
//-----------------------------------------------------------------
Scene::Scene(const std::string& name)
	: m_Name(name)
{
}


//-----------------------------------------------------------------
// Public Member Functions
//-----------------------------------------------------------------
void Scene::Init()
{
	for (const auto& go : m_Objects)
	{
		go->Init();
	}
}

void Scene::UpdateGui()
{
	for (const auto& go : m_Objects)
	{
		go->UpdateGui();
	}
}

void Scene::Update()
{
	for (const auto& go : m_Objects)
	{
		go->Update();
	}
}

void Scene::Render() const
{
	for (const auto& go : m_Objects)
	{
		go->Render();
	}
}

void Scene::Cleanup()
{
	for (const auto& go : m_Objects)
	{
		if (go->IsDestroyed()) go->OnDestroy();
	}

	std::erase_if(m_Objects, [](const std::shared_ptr<GameObject>& go) {
		return go->IsDestroyed();
		});

	for (const auto& go : m_Objects)
	{
		go->Cleanup();
	}
}

void Scene::Add(std::shared_ptr<GameObject> object)
{
	if (object->m_pScene == nullptr && object->GetParent() == nullptr)
	{
		object->m_pScene = this;
		m_Objects.emplace_back(std::move(object));
	}
	else
	{
		std::cout << "Failed to add object to scene.\n";
	}
}

void Scene::Remove(std::shared_ptr<GameObject> object)
{
	if (object->m_pScene == this)
	{
		object->m_pScene = nullptr;
	}
	std::erase(m_Objects, object);
}

void Scene::RemoveAll()
{
	for (auto& object : m_Objects)
	{
		object->m_pScene = nullptr;
	}
	m_Objects.clear();
}


//-----------------------------------------------------------------
// Private Member Functions
//-----------------------------------------------------------------

