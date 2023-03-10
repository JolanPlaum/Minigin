//-----------------------------------------------------------------
// Includes
//-----------------------------------------------------------------
#include "Scene.h"
#include "GameObject.h"
#include "Component.h"

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

void Scene::Add(std::shared_ptr<GameObject> object)
{
	if (object->m_pScene == nullptr)
	{
		object->m_pScene = this;
		m_Objects.emplace_back(std::move(object));
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

