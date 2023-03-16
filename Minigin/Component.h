#pragma once
#include "GameObject.h"

namespace dae
{
	//=============================
	// Base Component Class
	//=============================
	class Component
	{
	public:
		// Constructors and Destructor
		Component() = default;
		virtual ~Component() = default;

		// Copy and Move semantics
		Component(const Component& other)					= delete;
		Component& operator=(const Component& other)		= delete;
		Component(Component&& other) noexcept				= delete;
		Component& operator=(Component&& other) noexcept	= delete;

		// Public Member Functions
		virtual void Init() {};
		virtual void UpdateGui() {};
		virtual void Update() {};
		virtual void Render() const {};

		GameObject* GetGameObject() const { return m_pGameObject; }


	private:
		// Member variables
		friend class GameObject;
		GameObject* m_pGameObject = nullptr;
	};
}