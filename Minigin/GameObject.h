#pragma once
// Includes
#include "Object.h"
#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <typeinfo>
#include "Component.h"

namespace dae
{
	// Class Forward Declarations
	class Scene;
	class Transform;

	// Class Declaration
	class GameObject final : public Object
	{
	public:
		// Constructors and Destructor
		explicit GameObject();
		~GameObject();

		// Copy and Move semantics
		GameObject(const GameObject& other)					= delete;
		GameObject& operator=(const GameObject& other)		= delete;
		GameObject(GameObject&& other) noexcept				= delete;
		GameObject& operator=(GameObject&& other) noexcept	= delete;

		//---------------------------
		// Public Member Functions
		//---------------------------
		template <typename Comp> Comp* AddComponent();
		template <typename Comp> Comp* GetComponent() const;
		template <typename Comp> Comp* GetComponentInChildren() const;
		template <typename Comp> Comp* GetComponentInParent() const;
		template <typename Comp> std::vector<Comp*> GetComponents() const;
		template <typename Comp> std::vector<Comp*> GetComponentsInChildren() const;
		template <typename Comp> std::vector<Comp*> GetComponentsInParent() const;
		template <typename Comp> void RemoveComponent();
		template <typename Comp> bool HasComponent() const;

		void Init();
		void UpdateGui();
		void Update();
		void Render() const;
		void Cleanup();

		void OnDestroy() override;

		void SetParent(GameObject* pParent, bool keepWorldPosition = true);
		void SetTag(const std::string& tag);

		Transform& GetTransform() const { return *m_pTransform; }
		GameObject* GetParent() const { return m_pParent; }
		const std::vector<std::unique_ptr<GameObject>>& GetChildren() const { return m_Children; }
		std::string GetTag() const { return m_Tag; }


	private:
		// Member variables
		//todo: get rid of friend
		friend Scene;
		Scene* m_pScene{ nullptr };
		std::string m_Tag{ "Untagged" };

		GameObject* m_pParent{};
		std::vector<std::unique_ptr<GameObject>> m_Children{};

		std::unique_ptr<Transform> m_pTransform{};
		std::vector<std::unique_ptr<Component>> m_Components{};
		std::vector<Component*> m_NewComponents{};
		std::vector<Component*> m_ActiveComponents{};

		//---------------------------
		// Private Member Functions
		//---------------------------
		void AddChild(std::unique_ptr<GameObject> pChild);
		std::unique_ptr<GameObject> RemoveChild(GameObject* pChild);

		void CleanupComponents();
		void CleanupChildren();

		Scene* GetScene() const;

	};

	//todo: add checks to component functions to keep the transform component in mind
	//		either add or ignore if this is the case depending on the function

	template<typename Comp>
	inline Comp* GameObject::AddComponent()
	{
		if (HasComponent<Comp>())
		{
			std::cout << "Component of type \"" << typeid(Comp).name() << "\" already exists.\n";
			return nullptr;
		}

		m_Components.emplace_back(std::make_unique<Comp>(this));
		m_NewComponents.push_back(m_Components.back().get());
		return static_cast<Comp*>(m_Components.back().get());
	}

	template<typename Comp>
	inline Comp* GameObject::GetComponent() const
	{
		for (const auto& component : m_Components)
		{
			if (dynamic_cast<Comp*>(component.get()) != nullptr)
			{
				return static_cast<Comp*>(component.get());
			}
		}

		return nullptr;
	}

	template<typename Comp>
	inline Comp* GameObject::GetComponentInChildren() const
	{
		Comp* result = GetComponent<Comp>();

		if (result) return result;

		for (const auto& child : m_Children)
		{
			result = child->GetComponentInChildren<Comp>();
			if (result) return result;
		}

		return result;
	}

	template<typename Comp>
	inline Comp* GameObject::GetComponentInParent() const
	{
		Comp* result = GetComponent<Comp>();

		if (result) return result;

		return m_pParent->GetComponentInParent<Comp>();
	}

	template<typename Comp>
	inline void GameObject::RemoveComponent()
	{
		auto it = std::find_if(
			m_Components.begin(),
			m_Components.end(),
			[](const std::unique_ptr<Component>& component)
			{
				return (typeid(*component) == typeid(Comp));
			}
		);

		if (it != m_Components.end())
		{
			//todo: swap with last element and remove the last element from vector
			std::erase(m_NewComponents, it->get());
			std::erase(m_ActiveComponents, it->get());
			m_Components.erase(it);
		}
	}

	template<typename Comp>
	inline bool GameObject::HasComponent() const
	{
		auto it = std::find_if(
			m_Components.begin(),
			m_Components.end(),
			[](const std::unique_ptr<Component>& component){
				return (typeid(*component) == typeid(Comp));
			}
		);

		return (it != m_Components.end());
	}

	template<typename Comp>
	inline std::vector<Comp*> GameObject::GetComponents() const
	{
		std::vector<Comp*> result{};

		for (const auto& component : m_Components)
		{
			if (dynamic_cast<Comp*>(component.get()) != nullptr)
			{
				result.emplace_back(static_cast<Comp*>(component.get()));
			}
		}

		return result;
	}

	template<typename Comp>
	inline std::vector<Comp*> GameObject::GetComponentsInChildren() const
	{
		std::vector<Comp*> result;

		result = std::move(GetComponents<Comp>());

		for (const auto& child : m_Children)
		{
			auto otherResult = child->GetComponentsInChildren<Comp>();
			result.insert(result.end(), otherResult.begin(), otherResult.end());
		}

		return result;
	}

	template<typename Comp>
	inline std::vector<Comp*> GameObject::GetComponentsInParent() const
	{
		std::vector<Comp*> result;

		result = std::move(GetComponents<Comp>());

		if (m_pParent)
		{
			auto otherResult = m_pParent->GetComponentsInParent<Comp>();
			result.insert(result.end(), otherResult.begin(), otherResult.end());
		}

		return result;
	}
}
