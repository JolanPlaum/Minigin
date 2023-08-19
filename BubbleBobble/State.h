#pragma once
#include <memory>

namespace dae
{
	//=============================
	// Base State Class
	//=============================
	class State
	{
	public:
		// Constructors and Destructor
		explicit State() = default;
		virtual ~State() = default;
		
		// Copy and Move semantics
		State(const State& other)					= delete;
		State& operator=(const State& other)		= delete;
		State(State&& other) noexcept				= delete;
		State& operator=(State&& other) noexcept	= delete;

		// Public Member Functions
		virtual void OnEnter() = 0;
		virtual void OnExit() = 0;
		virtual void Update() = 0;
		virtual std::unique_ptr<State> Transition() = 0;
	};


	//=============================
	// GameObject State Class
	//=============================
	class GameObject;
	class GameObjectState : public State
	{
	public:
		// Constructors and Destructor
		explicit GameObjectState(GameObject* pGameObject) :m_pGameObject{ pGameObject } {}
		virtual ~GameObjectState() = default;

		// Copy and Move semantics
		GameObjectState(const GameObjectState& other) = delete;
		GameObjectState& operator=(const GameObjectState& other) = delete;
		GameObjectState(GameObjectState&& other) noexcept = delete;
		GameObjectState& operator=(GameObjectState&& other) noexcept = delete;

		// Public Member Functions
		virtual void OnEnter() override = 0;
		virtual void OnExit() override = 0;
		virtual void Update() override = 0;
		virtual std::unique_ptr<State> Transition() override = 0;


	private:
		// Member variables
		GameObject* m_pGameObject;

	protected:
		GameObject* GetGameObject() const { return m_pGameObject; }
	};
}

