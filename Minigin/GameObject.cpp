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
	for (const auto& component : m_NewComponents)
	{
		component->Init();
		m_ActiveComponents.push_back(component);
	}
	m_NewComponents.clear();

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
	for (const auto& component : m_ActiveComponents)
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
	for (const auto& component : m_ActiveComponents)
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
	// Exit early if nothing changes
	if (pParent == this || pParent == m_pParent || GetScene() == nullptr) return;

	// Update world transformations to the latest
	m_pTransform->ClearDirtyFlags();

	// Keep reference to scene of previous parent
	Scene* pOldScene = GetScene();

	// Remove self as a child from previous parent/scene
	std::unique_ptr<GameObject> pThis;
	if (m_pParent) pThis = m_pParent->RemoveChild(this);
	else pThis = pOldScene->Remove(this);

	// Set given parent on self
	m_pParent = pParent;

	// Add self as a child to given parent/scene
	if (m_pParent) m_pParent->AddChild(std::move(pThis));
	else pOldScene->Add(std::move(pThis));

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

void GameObject::SetTag(const std::string& tag)
{
	if (tag.empty()) m_Tag = "Untagged";
	else m_Tag = tag;
}


//-----------------------------------------------------------------
// Private Member Functions
//-----------------------------------------------------------------
void GameObject::AddChild(std::unique_ptr<GameObject> pChild)
{
	m_Children.emplace_back(std::move(pChild));
}

std::unique_ptr<GameObject> GameObject::RemoveChild(GameObject* pChild)
{
	auto it = std::find_if(m_Children.begin(), m_Children.end(),
		[pChild](const std::unique_ptr<GameObject>& go) {
			return go.get() == pChild;
		});

	std::unique_ptr<GameObject> pTemp;
	if (it != m_Children.end())
	{
		pTemp = std::move(*it);
		m_Children.erase(it);
	}
	return std::move(pTemp);
}

void GameObject::CleanupComponents()
{
	bool needsCleanup{ false };
	for (const auto& component : m_Components)
	{
		if (component->IsDestroyed())
		{
			component->OnDestroy();
			needsCleanup = true;
		}
	}

	if (needsCleanup)
	{
		std::erase_if(m_NewComponents, [](Component* pComponent) {
			return pComponent->IsDestroyed();
			});
		std::erase_if(m_ActiveComponents, [](Component* pComponent) {
			return pComponent->IsDestroyed();
			});
		std::erase_if(m_Components, [](const std::unique_ptr<Component>& component) {
			return component->IsDestroyed();
			});
	};
}

void GameObject::CleanupChildren()
{
	for (const auto& child : m_Children)
	{
		if (child->IsDestroyed()) child->OnDestroy();
	}

	std::erase_if(m_Children, [](const std::unique_ptr<GameObject>& child) {
		return child->IsDestroyed();
		});
}

Scene* GameObject::GetScene() const
{
	if (m_pScene) return m_pScene;

	if (m_pParent) return m_pParent->GetScene();

	return nullptr;
}

