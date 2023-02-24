//-----------------------------------------------------------------
// Includes
//-----------------------------------------------------------------
#include "Scene.h"
#include "GameObject.h"

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
}

void Scene::Update()
{
	//todo: implement update function
	//for(auto& object : m_objects)
	//{
	//	object->Update();
	//}
}

void Scene::Render() const
{
	//todo: implement render function
	//for (const auto& object : m_objects)
	//{
	//	object->Render();
	//}
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
		m_Objects.erase(std::remove(m_Objects.begin(), m_Objects.end(), object), m_Objects.end());
	}
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
