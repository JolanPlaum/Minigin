#pragma once
// Includes
#include <string>
#include "State.h"
#include "MoveCommand.h"
#include "DelegateHandle.h"

namespace dae
{
	// Class Forward Declarations
	class CSpriteRenderer;

	//=============================
	// BubbleStateLaunching
	//=============================
	class BubbleStateLaunching final : public GameObjectState
	{
	public:
		// Constructors and Destructor
		explicit BubbleStateLaunching(GameObject* pGameObject, std::unique_ptr<MoveCommand> pCommand)
			: GameObjectState(pGameObject)
			, m_pMoveCommand{ std::move(pCommand) }
		{
		}
		~BubbleStateLaunching() = default;

		// Copy and Move semantics
		BubbleStateLaunching(const BubbleStateLaunching& other)					= delete;
		BubbleStateLaunching& operator=(const BubbleStateLaunching& other)		= delete;
		BubbleStateLaunching(BubbleStateLaunching&& other) noexcept				= delete;
		BubbleStateLaunching& operator=(BubbleStateLaunching&& other) noexcept	= delete;

		// Public Member Functions
		void OnEnter() override;
		void OnExit() override;
		void Update() override;
		std::unique_ptr<State> Transition() override;


	private:
		// Member variables
		const float m_LaunchTime{ 0.35f };
		float m_AccuSec{ 0.f };

		std::unique_ptr<MoveCommand> m_pMoveCommand{};

		DelegateHandle m_CollisionHandle{};

		// Private Member Functions
		void OnCollisionNotify(GameObject* pOther);

	};

	//=============================
	// BubbleStateFloating
	//=============================
	class BubbleStateFloating final : public GameObjectState
	{
	public:
		// Constructors and Destructor
		explicit BubbleStateFloating(GameObject* pGameObject, std::string enemy = "")
			: GameObjectState(pGameObject)
			, m_EnemyName{ enemy }
		{
		}
		~BubbleStateFloating() = default;

		// Copy and Move semantics
		BubbleStateFloating(const BubbleStateFloating& other)					= delete;
		BubbleStateFloating& operator=(const BubbleStateFloating& other)		= delete;
		BubbleStateFloating(BubbleStateFloating&& other) noexcept				= delete;
		BubbleStateFloating& operator=(BubbleStateFloating&& other) noexcept	= delete;

		// Public Member Functions
		void OnEnter() override;
		void OnExit() override;
		void Update() override;
		std::unique_ptr<State> Transition() override;


	private:
		// Member variables
		const float m_MinTime{ 4.f }, m_MaxTime{ 10.f };
		const float m_MinEnemyTime{ 30.f }, m_MaxEnemyTime{ 60.f };
		float m_AccuSec{ 0.f }, m_Timer{ 0.f };
		std::string m_EnemyName{};

		// Private Member Functions

	};

	//=============================
	// BubbleStateBreaking
	//=============================
	class BubbleStateBreaking final : public GameObjectState
	{
	public:
		// Constructors and Destructor
		explicit BubbleStateBreaking(GameObject* pGameObject, std::string enemy = "")
			: GameObjectState(pGameObject)
			, m_EnemyName{ enemy }
		{
		}
		~BubbleStateBreaking() = default;

		// Copy and Move semantics
		BubbleStateBreaking(const BubbleStateBreaking& other)					= delete;
		BubbleStateBreaking& operator=(const BubbleStateBreaking& other)		= delete;
		BubbleStateBreaking(BubbleStateBreaking&& other) noexcept				= delete;
		BubbleStateBreaking& operator=(BubbleStateBreaking&& other) noexcept	= delete;

		// Public Member Functions
		void OnEnter() override;
		void OnExit() override;
		void Update() override;
		std::unique_ptr<State> Transition() override;


	private:
		// Member variables
		std::string m_EnemyName{};

		const float m_FirstFrameTime{ 2.f }, m_SecondFrameTime{ 1.f }, m_FlickerTime{ 1.f };
		float m_AccuSec{ 0.f };
		int m_FrameCount{ 0 };

		CSpriteRenderer* m_pRenderer{};
		DelegateHandle m_AnimationPlay{};

		// Private Member Functions
		void OnAnimationPlay();

	};
	
	//=============================
	// BubbleStatePop
	//=============================
	class BubbleStatePop final : public GameObjectState
	{
	public:
		// Constructors and Destructor
		explicit BubbleStatePop(GameObject* pGameObject) :GameObjectState(pGameObject) {};
		~BubbleStatePop() = default;
		
		// Copy and Move semantics
		BubbleStatePop(const BubbleStatePop& other)					= delete;
		BubbleStatePop& operator=(const BubbleStatePop& other)		= delete;
		BubbleStatePop(BubbleStatePop&& other) noexcept				= delete;
		BubbleStatePop& operator=(BubbleStatePop&& other) noexcept	= delete;
		
		// Public Member Functions
		void OnEnter() override;
		void OnExit() override;
		void Update() override;
		std::unique_ptr<State> Transition() override;
		
		
	private:
		// Member variables
		DelegateHandle m_AnimationEndHandle{};

		// Private Member Functions
		void OnAnimationEnd();
		
	};
}

