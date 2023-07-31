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
	m_pTransform = std::make_unique<Transform>(this);
}


//-----------------------------------------------------------------
// Destructor
//-----------------------------------------------------------------
GameObject::~GameObject()
{
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

void GameObject::UpdateGui()
{
	for (const auto& component : m_Components)
	{
		component->UpdateGui();
	}

	for (const auto& child : m_Children)
	{
		child->UpdateGui();
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

void GameObject::Cleanup()
{
	CleanupComponents();
	CleanupChildren();

	for (const auto& child : m_Children)
	{
		child->Cleanup();
	}
}

void GameObject::OnDestroy()
{
	for (const auto& component : m_Components)
	{
		component->OnDestroy();
	}

	for (const auto& child : m_Children)
	{
		child->OnDestroy();
	}
}

void GameObject::SetParent(GameObject* pParent, bool keepWorldPosition)
{
	// Ensure this GameObject stays alive
	auto pThis = shared_from_this();

	// Update world transformations to the latest
	m_pTransform->ClearDirtyFlags();

	// Keep reference to scene of previous parent
	Scene* pOldScene = GetScene();

	// Remove self as a child from previous parent
	if (m_pParent) m_pParent->RemoveChild(pThis);

	// Set given parent on self
	m_pParent = pParent;

	// Add self as a child to given parent
	if (m_pParent) m_pParent->AddChild(pThis);

	// Remove/Add self from/to scene it was previously in
	if (pOldScene)
	{
		if (m_pParent) pOldScene->Remove(pThis);
		else pOldScene->Add(pThis);
	}

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

void GameObject::SetTag(const std::string& tag)
{
	if (tag.empty()) m_Tag = "Untagged";
	else m_Tag = tag;
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

void GameObject::CleanupComponents()
{
	for (const auto& component : m_Components)
	{
		if (component->IsDestroyed()) component->OnDestroy();
	}

	std::erase_if(m_Components, [](const std::unique_ptr<Component>& component) {
			return component->IsDestroyed();
		});
}

void GameObject::CleanupChildren()
{
	for (const auto& child : m_Children)
	{
		if (child->IsDestroyed()) child->OnDestroy();
	}

	std::erase_if(m_Children, [](const std::shared_ptr<GameObject>& child) {
		return child->IsDestroyed();
		});
}

Scene* GameObject::GetScene() const
{
	if (m_pScene) return m_pScene;

	if (m_pParent) return m_pParent->GetScene();

	return nullptr;
}

