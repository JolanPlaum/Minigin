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
}

void Scene::Update()
{
	for (const auto& comp : m_BehaviourComponents)
	{
		comp->Update();
	}
}

void Scene::Render() const
{
	for (const auto& comp : m_RenderComponents)
	{
		comp->Render();
	}
}

void Scene::Add(std::shared_ptr<GameObject> object)
{
	if (object->m_pScene == nullptr)
	{
		object->m_pScene = this;
		AddRenderComponents(*object);
		AddBehaviourComponents(*object);

		m_Objects.emplace_back(std::move(object));
	}
}

void Scene::Remove(std::shared_ptr<GameObject> object)
{
	if (object->m_pScene == this)
	{
		object->m_pScene = nullptr;
		RemoveRenderComponents(object.get());
		RemoveBehaviourComponents(object.get());

		std::erase(m_Objects, object);
	}
}

void Scene::RemoveAll()
{
	for (auto& object : m_Objects)
	{
		object->m_pScene = nullptr;
	}
	m_Objects.clear();
	m_RenderComponents.clear();
	m_BehaviourComponents.clear();
}


//-----------------------------------------------------------------
// Private Member Functions
//-----------------------------------------------------------------
void Scene::AddRenderComponents(const GameObject& object)
{
	const auto& comps = object.GetComponents<RenderComponent>();
	m_RenderComponents.insert(m_RenderComponents.end(), comps.begin(), comps.end());
}

void Scene::AddBehaviourComponents(const GameObject& object)
{
	const auto& comps = object.GetComponents<BehaviourComponent>();
	m_BehaviourComponents.insert(m_BehaviourComponents.end(), comps.begin(), comps.end());
}

void Scene::RemoveRenderComponents(const GameObject* pObject)
{
	std::erase_if(m_RenderComponents,
		[pObject](const std::shared_ptr<RenderComponent>& comp){
			return *comp.get() == pObject;
		});
}

void Scene::RemoveBehaviourComponents(const GameObject* pObject)
{
	std::erase_if(m_BehaviourComponents,
		[pObject](const std::shared_ptr<BehaviourComponent>& comp){
			return *comp.get() == pObject;
		});
}

