#pragma once
// Includes
#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <typeinfo>
#include "Component.h"

namespace dae
{
	// Class Forward Declarations

	// Class Declaration
	class GameObject final
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
		template <typename Comp> std::weak_ptr<Comp> GetComponent();
		template <typename Comp> void RemoveComponent();
		template <typename Comp> bool HasComponent();


	private:
		// Member variables
		std::vector<std::shared_ptr<Component>> m_Components{};

		//---------------------------
		// Private Member Functions
		//---------------------------

	};

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
	inline std::weak_ptr<Comp> GameObject::GetComponent()
	{
		for (const auto& component : m_Components)
		{
			if (typeid(*component.get()) == typeid(Comp))
			{
				return std::static_pointer_cast<Comp>(component);
			}
		}

		std::cout << "Component of type \"" << typeid(Comp).name() << "\" doesn't exists.\n";
		return std::shared_ptr<Comp>(nullptr);
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
	inline bool GameObject::HasComponent()
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
}
