#pragma once
// Includes
#include <vector>
#include <glm/vec2.hpp>
#include "State.h"
#include "DelegateHandle.h"
#include "MoveCommand.h"

namespace dae
{
	// Class Forward Declarations
	class Dragon;
	class EntityCollision;
	class CSpriteRenderer;
	class Command;

	//=============================
	// DragonPlayerStateIdle
	//=============================
	class DragonPlayerStateIdle final : public GameObjectState
	{
	public:
		// Constructors and Destructor
		explicit DragonPlayerStateIdle(GameObject* pGameObject) :GameObjectState(pGameObject) {};
		~DragonPlayerStateIdle() = default;
		
		// Copy and Move semantics
		DragonPlayerStateIdle(const DragonPlayerStateIdle& other)					= delete;
		DragonPlayerStateIdle& operator=(const DragonPlayerStateIdle& other)		= delete;
		DragonPlayerStateIdle(DragonPlayerStateIdle&& other) noexcept				= delete;
		DragonPlayerStateIdle& operator=(DragonPlayerStateIdle&& other) noexcept	= delete;
		
		// Public Member Functions
		void OnEnter() override;
		void OnExit() override;
		void Update() override;
		std::unique_ptr<State> Transition() override;
		
		
	private:
		// Member variables
		EntityCollision* m_pEntityCollision{};
		std::vector<Command*> m_KeyboardCommands{};
		std::vector<Command*> m_GamepadCommands{};

		std::unique_ptr<MoveCommand> m_pMoveCommand{};
		
		// Private Member Functions
		
	};

	//=============================
	// DragonPlayerStateWalking
	//=============================
	class DragonPlayerStateWalking final : public GameObjectState
	{
	public:
		// Constructors and Destructor
		explicit DragonPlayerStateWalking(GameObject* pGameObject) :GameObjectState(pGameObject) {};
		~DragonPlayerStateWalking() = default;

		// Copy and Move semantics
		DragonPlayerStateWalking(const DragonPlayerStateWalking& other)					= delete;
		DragonPlayerStateWalking& operator=(const DragonPlayerStateWalking& other)		= delete;
		DragonPlayerStateWalking(DragonPlayerStateWalking&& other) noexcept				= delete;
		DragonPlayerStateWalking& operator=(DragonPlayerStateWalking&& other) noexcept	= delete;

		// Public Member Functions
		void OnEnter() override;
		void OnExit() override;
		void Update() override;
		std::unique_ptr<State> Transition() override;


	private:
		// Member variables
		EntityCollision* m_pEntityCollision{};
		std::vector<Command*> m_KeyboardCommands{};
		std::vector<Command*> m_GamepadCommands{};

		std::unique_ptr<MoveCommand> m_pMoveCommand{};

		// Private Member Functions

	};
	
	//=============================
	// DragonPlayerStateJumping
	//=============================
	class DragonPlayerStateJumping final : public GameObjectState
	{
	public:
		// Constructors and Destructor
		explicit DragonPlayerStateJumping(GameObject* pGameObject) :GameObjectState(pGameObject) {};
		~DragonPlayerStateJumping() = default;
		
		// Copy and Move semantics
		DragonPlayerStateJumping(const DragonPlayerStateJumping& other)					= delete;
		DragonPlayerStateJumping& operator=(const DragonPlayerStateJumping& other)		= delete;
		DragonPlayerStateJumping(DragonPlayerStateJumping&& other) noexcept				= delete;
		DragonPlayerStateJumping& operator=(DragonPlayerStateJumping&& other) noexcept	= delete;
		
		// Public Member Functions
		void OnEnter() override;
		void OnExit() override;
		void Update() override;
		std::unique_ptr<State> Transition() override;
		
		
	private:
		// Member variables
		EntityCollision* m_pEntityCollision{};
		std::vector<Command*> m_KeyboardCommands{};
		std::vector<Command*> m_GamepadCommands{};

		bool m_IsFalling{ false };
		const float m_JumpTime{ 0.5f };
		float m_AccuSec{ 0.f };
		std::unique_ptr<MoveCommand> m_pMoveCommand{};
		
		// Private Member Functions
		
	};

	//=============================
	// DragonPlayerStateFalling
	//=============================
	class DragonPlayerStateFalling final : public GameObjectState
	{
	public:
		// Constructors and Destructor
		explicit DragonPlayerStateFalling(GameObject* pGameObject) :GameObjectState(pGameObject) {};
		~DragonPlayerStateFalling() = default;

		// Copy and Move semantics
		DragonPlayerStateFalling(const DragonPlayerStateFalling& other)					= delete;
		DragonPlayerStateFalling& operator=(const DragonPlayerStateFalling& other)		= delete;
		DragonPlayerStateFalling(DragonPlayerStateFalling&& other) noexcept				= delete;
		DragonPlayerStateFalling& operator=(DragonPlayerStateFalling&& other) noexcept	= delete;

		// Public Member Functions
		void OnEnter() override;
		void OnExit() override;
		void Update() override;
		std::unique_ptr<State> Transition() override;


	private:
		// Member variables
		EntityCollision* m_pEntityCollision{};
		std::vector<Command*> m_KeyboardCommands{};
		std::vector<Command*> m_GamepadCommands{};

		std::unique_ptr<MoveCommand> m_pMoveCommand{};

		// Private Member Functions

	};

	//=============================
	// DragonPlayerStateDeath
	//=============================
	class DragonPlayerStateDeath final : public GameObjectState
	{
	public:
		// Constructors and Destructor
		explicit DragonPlayerStateDeath(GameObject* pGameObject) :GameObjectState(pGameObject) {};
		~DragonPlayerStateDeath() = default;

		// Copy and Move semantics
		DragonPlayerStateDeath(const DragonPlayerStateDeath& other)					= delete;
		DragonPlayerStateDeath& operator=(const DragonPlayerStateDeath& other)		= delete;
		DragonPlayerStateDeath(DragonPlayerStateDeath&& other) noexcept				= delete;
		DragonPlayerStateDeath& operator=(DragonPlayerStateDeath&& other) noexcept	= delete;

		// Public Member Functions
		void OnEnter() override;
		void OnExit() override;
		void Update() override;
		std::unique_ptr<State> Transition() override;


	private:
		// Member variables
		const float m_FirstFrameTime{ 0.5f }, m_DeathAnim1Time{ 0.875f }, m_DeathAnim2Time{ 1.f };
		float m_AccuSec{ 0.f }, m_Timer{ 0.f };
		bool m_IsAnim2{ false }, m_NeedsRespawn{ false };

		// Private Member Functions

	};
	
	//=============================
	// DragonPlayerStateWin
	//=============================
	class DragonPlayerStateWin final : public GameObjectState
	{
	public:
		// Constructors and Destructor
		explicit DragonPlayerStateWin(GameObject* pGameObject) :GameObjectState(pGameObject) {};
		~DragonPlayerStateWin() = default;
		
		// Copy and Move semantics
		DragonPlayerStateWin(const DragonPlayerStateWin& other)					= delete;
		DragonPlayerStateWin& operator=(const DragonPlayerStateWin& other)		= delete;
		DragonPlayerStateWin(DragonPlayerStateWin&& other) noexcept				= delete;
		DragonPlayerStateWin& operator=(DragonPlayerStateWin&& other) noexcept	= delete;
		
		// Public Member Functions
		void OnEnter() override;
		void OnExit() override;
		void Update() override;
		std::unique_ptr<State> Transition() override;
		
		
	private:
		// Member variables
		bool m_IsAtStartPos{ false }, m_NeedsRespawn{ false };
		int m_CurrentAnim{ 1 };

		Dragon* m_pDragonOwner{};
		CSpriteRenderer* m_pRenderer{};
		EntityCollision* m_pEntityCollision{};

		std::unique_ptr<MoveCommand> m_pMoveCommand{};

		DelegateHandle m_AnimationEndHandle{};
		
		// Private Member Functions
		void OnAnimationEnd();
		
	};
}

