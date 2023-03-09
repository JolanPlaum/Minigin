//-----------------------------------------------------------------
// Includes
//-----------------------------------------------------------------
#include "GameObject.h"
#include "Transform.h"
#include "Scene.h"

using namespace dae;


//-----------------------------------------------------------------
// Constructors
//-----------------------------------------------------------------
GameObject::GameObject()
{
	m_pTransform = std::make_unique<Transform>();
	m_pTransform->m_pGameObject = this;
}


//-----------------------------------------------------------------
// Destructor
//-----------------------------------------------------------------
GameObject::~GameObject()
{
	for (const auto& component : m_Components)
	{
		component->m_pGameObject = nullptr;
	}
}


//-----------------------------------------------------------------
// Public Member Functions
//-----------------------------------------------------------------
void GameObject::Init()
{
	for (const auto& component : m_Components)
	{
		component->Init();
	}

	for (const auto& child : m_Children)
	{
		child->Init();
	}
}

void GameObject::Update()
{
	for (const auto& component : m_Components)
	{
		component->Update();
	}

	for (const auto& child : m_Children)
	{
		child->Update();
	}
}

void GameObject::Render() const
{
	for (const auto& component : m_Components)
	{
		component->Render();
	}

	for (const auto& child : m_Children)
	{
		child->Render();
	}
}

void GameObject::SetParent(GameObject* pParent, bool keepWorldPosition)
{
	// Update world transformations to the latest
	m_pTransform->ClearDirtyFlags();

	// Remove/Add self from/to scene it's currently in
	Scene* pScene = GetScene();
	if (pScene)
	{
		if (pParent) pScene->Remove(shared_from_this());
		else pScene->Add(shared_from_this());
	}

	// Remove self as a child from previous parent
	if (m_pParent) m_pParent->RemoveChild(shared_from_this());

	// Set given parent on self
	m_pParent = pParent;

	// Add self as a child to given parent
	if (m_pParent) m_pParent->AddChild(shared_from_this());

	// Update transform
	if (keepWorldPosition)
	{
		m_pTransform->SetWorldPosition(m_pTransform->GetWorldPosition());
		m_pTransform->SetWorldRotation(m_pTransform->GetWorldRotation());
		m_pTransform->SetWorldScale(m_pTransform->GetWorldScale());
	}
	else
	{
		//make sure the flag is dirty since we have a new parent
		m_pTransform->SetLocalPosition(m_pTransform->GetLocalPosition());
		m_pTransform->SetLocalRotation(m_pTransform->GetLocalRotation());
		m_pTransform->SetLocalScale(m_pTransform->GetLocalScale());
	}
}

void GameObject::SetParent(const std::shared_ptr<GameObject>& pParent, bool keepWorldPosition)
{
	SetParent(pParent.get(), keepWorldPosition);
}


//-----------------------------------------------------------------
// Private Member Functions
//-----------------------------------------------------------------
void GameObject::AddChild(std::shared_ptr<GameObject> pChild)
{
	m_Children.push_back(pChild);
}

void GameObject::RemoveChild(std::shared_ptr<GameObject> pChild)
{
	std::erase(m_Children, pChild);
}

Scene* GameObject::GetScene() const
{
	if (m_pScene) return m_pScene;

	if (m_pParent) return m_pParent->GetScene();

	return nullptr;
}

