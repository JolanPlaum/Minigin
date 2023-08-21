#pragma once
// Includes
#include "State.h"
#include "MoveCommand.h"

namespace dae
{
	// Class Forward Declarations
	class CSpriteRenderer;
	class EntityCollision;
	
	//=============================
	// ZenChanWaitForJump
	//=============================
	class ZenChanWaitForJump final : public GameObjectState
	{
	public:
		// Constructors and Destructor
		explicit ZenChanWaitForJump(GameObject* pGameObject) :GameObjectState(pGameObject) {};
		~ZenChanWaitForJump() = default;
		
		// Copy and Move semantics
		ZenChanWaitForJump(const ZenChanWaitForJump& other)					= delete;
		ZenChanWaitForJump& operator=(const ZenChanWaitForJump& other)		= delete;
		ZenChanWaitForJump(ZenChanWaitForJump&& other) noexcept				= delete;
		ZenChanWaitForJump& operator=(ZenChanWaitForJump&& other) noexcept	= delete;
		
		// Public Member Functions
		void OnEnter() override;
		void OnExit() override;
		void Update() override;
		std::unique_ptr<State> Transition() override;
		
		
	private:
		// Member variables
		const float m_WaitTimer{ 0.5f };
		float m_AccuSec{ 0.f };
		bool m_IsFlipped{ false };

		CSpriteRenderer* m_pRenderer{};
		
		// Private Member Functions
		
	};
	
	//=============================
	// ZenChanJump
	//=============================
	class ZenChanJump final : public GameObjectState
	{
	public:
		// Constructors and Destructor
		explicit ZenChanJump(GameObject* pGameObject) :GameObjectState(pGameObject) {};
		~ZenChanJump() = default;
		
		// Copy and Move semantics
		ZenChanJump(const ZenChanJump& other)					= delete;
		ZenChanJump& operator=(const ZenChanJump& other)		= delete;
		ZenChanJump(ZenChanJump&& other) noexcept				= delete;
		ZenChanJump& operator=(ZenChanJump&& other) noexcept	= delete;
		
		// Public Member Functions
		void OnEnter() override;
		void OnExit() override;
		void Update() override;
		std::unique_ptr<State> Transition() override;
		
		
	private:
		// Member variables
		const float m_JumpTime{ 0.5f };
		float m_AccuSec{ 0.f };
		std::unique_ptr<MoveCommand> m_pMoveCommand{};
		
		// Private Member Functions
		
	};
	
	//=============================
	// ZenChanFall
	//=============================
	class ZenChanFall final : public GameObjectState
	{
	public:
		// Constructors and Destructor
		explicit ZenChanFall(GameObject* pGameObject) :GameObjectState(pGameObject) {};
		~ZenChanFall() = default;
		
		// Copy and Move semantics
		ZenChanFall(const ZenChanFall& other)					= delete;
		ZenChanFall& operator=(const ZenChanFall& other)		= delete;
		ZenChanFall(ZenChanFall&& other) noexcept				= delete;
		ZenChanFall& operator=(ZenChanFall&& other) noexcept	= delete;
		
		// Public Member Functions
		void OnEnter() override;
		void OnExit() override;
		void Update() override;
		std::unique_ptr<State> Transition() override;
		
		
	private:
		// Member variables
		EntityCollision* m_pEntityCollision{};
		std::unique_ptr<MoveCommand> m_pMoveCommand{};
		
		// Private Member Functions
		
	};
	
	//=============================
	// ZenChanWalk
	//=============================
	class ZenChanWalk final : public GameObjectState
	{
	public:
		// Constructors and Destructor
		explicit ZenChanWalk(GameObject* pGameObject) :GameObjectState(pGameObject) {};
		~ZenChanWalk() = default;
		
		// Copy and Move semantics
		ZenChanWalk(const ZenChanWalk& other)					= delete;
		ZenChanWalk& operator=(const ZenChanWalk& other)		= delete;
		ZenChanWalk(ZenChanWalk&& other) noexcept				= delete;
		ZenChanWalk& operator=(ZenChanWalk&& other) noexcept	= delete;
		
		// Public Member Functions
		void OnEnter() override;
		void OnExit() override;
		void Update() override;
		std::unique_ptr<State> Transition() override;
		
		
	private:
		// Member variables
		const float m_MinTime{ 1.f }, m_MaxTime{ 3.f };
		float m_AccuSec{ 0.f }, m_Timer{ 0.f };

		EntityCollision* m_pEntityCollision{};
		std::unique_ptr<MoveCommand> m_pMoveCommand{};
		
		// Private Member Functions
		
	};
	
	//=============================
	// ZenChanTrapped
	//=============================
	class ZenChanTrapped final : public GameObjectState
	{
	public:
		// Constructors and Destructor
		explicit ZenChanTrapped(GameObject* pGameObject) :GameObjectState(pGameObject) {};
		~ZenChanTrapped() = default;
		
		// Copy and Move semantics
		ZenChanTrapped(const ZenChanTrapped& other)					= delete;
		ZenChanTrapped& operator=(const ZenChanTrapped& other)		= delete;
		ZenChanTrapped(ZenChanTrapped&& other) noexcept				= delete;
		ZenChanTrapped& operator=(ZenChanTrapped&& other) noexcept	= delete;
		
		// Public Member Functions
		void OnEnter() override;
		void OnExit() override;
		void Update() override;
		std::unique_ptr<State> Transition() override;
		
		
	private:
		// Member variables
		
		// Private Member Functions
		
	};
	
	//=============================
	// ZenChanDeath
	//=============================
	class ZenChanDeath final : public GameObjectState
	{
	public:
		// Constructors and Destructor
		explicit ZenChanDeath(GameObject* pGameObject) :GameObjectState(pGameObject) {};
		~ZenChanDeath() = default;
		
		// Copy and Move semantics
		ZenChanDeath(const ZenChanDeath& other)					= delete;
		ZenChanDeath& operator=(const ZenChanDeath& other)		= delete;
		ZenChanDeath(ZenChanDeath&& other) noexcept				= delete;
		ZenChanDeath& operator=(ZenChanDeath&& other) noexcept	= delete;
		
		// Public Member Functions
		void OnEnter() override;
		void OnExit() override;
		void Update() override;
		std::unique_ptr<State> Transition() override;
		
		
	private:
		// Member variables
		const float m_DeathAnimTime{ 1.f };
		float m_AccuSec{ 0.f };
		
		// Private Member Functions
		
	};
}

