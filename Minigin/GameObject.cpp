//-----------------------------------------------------------------
// Includes
//-----------------------------------------------------------------
#include "GameObject.h"
#include "Transform.h"

using namespace dae;


//-----------------------------------------------------------------
// Constructors
//-----------------------------------------------------------------
GameObject::GameObject()
{
	AddComponent<Transform>();
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

void GameObject::SetParent(std::shared_ptr<GameObject> pParent, bool keepWorldPosition)
{
	// Remove self as a child from previous parent
	if (m_pParent.lock()) m_pParent.lock()->RemoveChild(shared_from_this());

	// Set given parent on self
	m_pParent = pParent;

	// Add self as a child to given parent
	if (pParent) pParent->AddChild(shared_from_this());

	// Update transform
	// todo: update transform
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

