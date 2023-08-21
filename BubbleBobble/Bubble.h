#pragma once
// Includes
#include "Component.h"
#include <memory>
#include <string>
#include "DelegateHandle.h"
#include "State.h"
#include "MoveCommand.h"

namespace dae
{
	// Class Forward Declarations
	class BoxCollider2D;
	class CSpriteRenderer;
	class EnemyBehaviour;
	
	// Class Declaration
	class Bubble final : public Component
	{
	public:
		// Constructors and Destructor
		Bubble(GameObject* pGameObject) :Component(pGameObject) {};
		~Bubble() = default;
		
		// Copy and Move semantics
		Bubble(const Bubble& other)					= delete;
		Bubble& operator=(const Bubble& other)		= delete;
		Bubble(Bubble&& other) noexcept				= delete;
		Bubble& operator=(Bubble&& other) noexcept	= delete;
		
		//---------------------------
		// Public Member Functions
		//---------------------------
		void Init() override;
		void OnDestroy() override;
		void Update() override;

		void Launch(std::unique_ptr<MoveCommand> pCommand);
		void TrapEnemy(GameObject* pEnemy);
		void EndOfLaunch();

		void SetColor(std::string color);
		std::string GetColor() const { return m_Color; }

		EnemyBehaviour* GetTrappedEnemy() const { return m_pTrappedEnemy; }
		
		
	private:
		// Member variables
		bool m_IsNotBeingLaunched{ true };

		bool m_IsEnemyAnimReverse{ false }, m_IsEnemyAnimStraight{ false };
		float m_EnemyAnimAccuSec{ 0.f };
		const float m_EnemyStraightAnimTimer{ 5.f / 60.f };
		const float m_EnemySideAnimTimer{ 20.f / 60.f };

		float m_HoverAccuSec{ 0.f };
		const float m_HoverSwitchTime{ 0.5f };

		std::string m_Color{};

		CSpriteRenderer* m_pSprite{};
		BoxCollider2D* m_pCollider{};
		EnemyBehaviour* m_pTrappedEnemy{};
		std::unique_ptr<State> m_pState{};
		std::unique_ptr<MoveCommand> m_pMoveCommand{};

		DelegateHandle m_CollisionHandle{};
		
		//---------------------------
		// Private Member Functions
		//---------------------------
		void OnCollisionNotify(GameObject* pOther);

		void UpdateEnemyAnimation();
		void UpdateMoveCommand();
		
	};
}

