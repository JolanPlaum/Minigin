//-----------------------------------------------------------------
// Includes
//-----------------------------------------------------------------
#include "Scene.h"
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

	std::erase_if(m_Objects, [](const std::unique_ptr<GameObject>& go) {
		return go->IsDestroyed();
		});

	for (const auto& go : m_Objects)
	{
		go->Cleanup();
	}
}

GameObject* Scene::CreateObject()
{
	return Add(std::move(std::make_unique<GameObject>()));
}

GameObject* Scene::Add(std::unique_ptr<GameObject> pObject)
{
	if (pObject == nullptr) return nullptr;

	if (pObject->m_pScene == nullptr && pObject->GetParent() == nullptr)
	{
		pObject->m_pScene = this;
		m_Objects.emplace_back(std::move(pObject));
		return m_Objects.back().get();
	}

	return nullptr;
}

std::unique_ptr<GameObject> Scene::Remove(GameObject* pObject)
{
	auto it = std::find_if(m_Objects.begin(), m_Objects.end(),
		[pObject](const std::unique_ptr<GameObject>& go) {
			return go.get() == pObject;
		});

	std::unique_ptr<GameObject> pTemp;
	if (it != m_Objects.end())
	{
		pTemp = std::move(*it);
		pTemp->m_pScene = nullptr;
		m_Objects.erase(it);
	}
	return std::move(pTemp);
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

