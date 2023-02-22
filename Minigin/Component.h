#pragma once

namespace dae
{
	class GameObject;

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

	private:
		// Member variables
		friend GameObject;
		GameObject* m_pGameObject = nullptr;
	};

	//=============================
	// Render Component Class
	//=============================
	class RenderComponent : public Component
	{
	public:
		// Constructors and Destructor
		RenderComponent() = default;
		virtual ~RenderComponent() = default;

		// Copy and Move semantics
		RenderComponent(const RenderComponent& other)					= delete;
		RenderComponent& operator=(const RenderComponent& other)		= delete;
		RenderComponent(RenderComponent&& other) noexcept				= delete;
		RenderComponent& operator=(RenderComponent&& other) noexcept	= delete;

		// Public Member Functions
		virtual void Render() const = 0;
	};

	//=============================
	// Behaviour Component Class
	//=============================
	class BehaviourComponent : public Component
	{
	public:
		// Constructors and Destructor
		BehaviourComponent() = default;
		virtual ~BehaviourComponent() = default;

		// Copy and Move semantics
		BehaviourComponent(const BehaviourComponent& other)					= delete;
		BehaviourComponent& operator=(const BehaviourComponent& other)		= delete;
		BehaviourComponent(BehaviourComponent&& other) noexcept				= delete;
		BehaviourComponent& operator=(BehaviourComponent&& other) noexcept	= delete;

		// Public Member Functions
		virtual void Update() = 0;
	};
}