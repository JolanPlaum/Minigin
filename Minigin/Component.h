#pragma once
#include "Object.h"

namespace dae
{
	class GameObject;

	//=============================
	// Base Component Class
	//=============================
	class Component : public Object
	{
	public:
		// Constructors and Destructor
		Component(GameObject* pGameObject) :m_pGameObject{ pGameObject } {};
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
		virtual void OnDestroy() override {};

		GameObject* GetGameObject() const { return m_pGameObject; }


	private:
		// Member variables
		GameObject* m_pGameObject = nullptr;
	};
}