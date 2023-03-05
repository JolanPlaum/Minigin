#pragma once
// Includes
#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <typeinfo>

namespace dae
{
	// Class Forward Declarations
	class Component;
	class Scene;
	class Transform;

	// Class Declaration
	class GameObject final : public std::enable_shared_from_this<GameObject>
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
		template <typename Comp> std::weak_ptr<Comp> AddComponent();
		template <typename Comp> std::weak_ptr<Comp> GetComponent() const;
		template <typename Comp> std::weak_ptr<Comp> GetComponentInChildren() const;
		template <typename Comp> std::weak_ptr<Comp> GetComponentInParent() const;
		template <typename Comp> void RemoveComponent();
		template <typename Comp> bool HasComponent() const;

		void Init();
		void Update();
		void Render() const;

		void SetParent(std::shared_ptr<GameObject> pParent, bool keepWorldPosition = true);

		bool GetDestroyed() const { return m_IsDestroyed; }
		Transform& GetTransform() const { return *m_pTransform; }
		std::weak_ptr<GameObject> GetParent() const { return m_pParent; }
		const std::vector<std::shared_ptr<GameObject>>& GetChildren() const { return m_Children; }


	private:
		// Member variables
		//todo: get rid of friend
		friend Scene;
		bool m_IsDestroyed{ false };
		Scene* m_pScene{ nullptr };

		std::weak_ptr<GameObject> m_pParent{};
		std::vector<std::shared_ptr<GameObject>> m_Children{};

		std::unique_ptr<Transform> m_pTransform{};
		std::vector<std::shared_ptr<Component>> m_Components{};

		//---------------------------
		// Private Member Functions
		//---------------------------
		template <typename Comp> std::vector<std::shared_ptr<Comp>> GetComponents() const;
		template <typename Comp> std::vector<std::shared_ptr<Comp>> GetComponentsInChildren() const;
		template <typename Comp> std::vector<std::shared_ptr<Comp>> GetComponentsInParent() const;

		void AddChild(std::shared_ptr<GameObject> pChild);
		void RemoveChild(std::shared_ptr<GameObject> pChild);

		Scene* GetScene() const;

	};

	//todo: add checks to component functions to keep the transform component in mind
	//		either add or ignore if this is the case depending on the function

	template<typename Comp>
	inline std::weak_ptr<Comp> GameObject::AddComponent()
	{
		if (HasComponent<Comp>())
		{
			std::cout << "Component of type \"" << typeid(Comp).name() << "\" already exists.\n";
			return std::shared_ptr<Comp>(nullptr);
		}

		m_Components.emplace_back(std::make_shared<Comp>());
		m_Components.back()->m_pGameObject = this;
		return std::static_pointer_cast<Comp>(m_Components.back());
	}

	template<typename Comp>
	inline std::weak_ptr<Comp> GameObject::GetComponent() const
	{
		for (const auto& component : m_Components)
		{
			if (dynamic_cast<Comp*>(component.get()) != nullptr)
			{
				return std::static_pointer_cast<Comp>(component);
			}
		}

		return std::shared_ptr<Comp>(nullptr);
	}

	template<typename Comp>
	inline std::weak_ptr<Comp> GameObject::GetComponentInChildren() const
	{
		std::weak_ptr<Comp> result = GetComponent<Comp>();

		if (result.lock()) return result;

		for (const auto& child : m_Children)
		{
			result = child->GetComponentInChildren<Comp>();
			if (result.lock()) return result;
		}

		return result;
	}

	template<typename Comp>
	inline std::weak_ptr<Comp> GameObject::GetComponentInParent() const
	{
		std::weak_ptr<Comp> result = GetComponent<Comp>();

		if (result.lock()) return result;

		return m_pParent.lock()->GetComponentInParent<Comp>();
	}

	template<typename Comp>
	inline void GameObject::RemoveComponent()
	{
		auto it = std::find_if(
			m_Components.begin(),
			m_Components.end(),
			[](const std::shared_ptr<Component>& component)
			{
				return (typeid(*component.get()) == typeid(Comp));
			}
		);

		if (it != m_Components.end())
		{
			//todo: swap with last element and remove the last element from vector
			m_Components.erase(it);
		}
	}

	template<typename Comp>
	inline bool GameObject::HasComponent() const
	{
		auto it = std::find_if(
			m_Components.begin(),
			m_Components.end(),
			[](const std::shared_ptr<Component>& component){
				return (typeid(*component.get()) == typeid(Comp));
			}
		);

		return (it != m_Components.end());
	}

	template<typename Comp>
	inline std::vector<std::shared_ptr<Comp>> GameObject::GetComponents() const
	{
		std::vector<std::shared_ptr<Comp>> result{};

		for (const auto& component : m_Components)
		{
			if (dynamic_cast<Comp*>(component.get()) != nullptr)
			{
				result.emplace_back(std::static_pointer_cast<Comp>(component));
			}
		}

		return result;
	}

	template<typename Comp>
	inline std::vector<std::shared_ptr<Comp>> GameObject::GetComponentsInChildren() const
	{
		std::vector<std::shared_ptr<Comp>> result;

		result = std::move(GetComponents<Comp>());

		for (const auto& child : m_Children)
		{
			auto otherResult = child->GetComponentsInChildren<Comp>();
			result.insert(result.end(), otherResult.begin(), otherResult.end());
		}

		return result;
	}

	template<typename Comp>
	inline std::vector<std::shared_ptr<Comp>> GameObject::GetComponentsInParent() const
	{
		std::vector<std::shared_ptr<Comp>> result;

		result = std::move(GetComponents<Comp>());

		if (!m_pParent.expired())
		{
			auto otherResult = m_pParent.lock()->GetComponentsInParent<Comp>();
			result.insert(result.end(), otherResult.begin(), otherResult.end());
		}

		return result;
	}
}
