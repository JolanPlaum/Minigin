#pragma once
// Includes
#include "Component.h"
#include <memory>
#include <glm/vec2.hpp>
#include "DelegateHandle.h"
#include "State.h"

namespace dae
{
	// Class Forward Declarations
	enum class Player : unsigned char
	{
		None,

		One,
		Two
	};
	
	// Class Declaration
	class Dragon final : public Component
	{
	public:
		// Constructors and Destructor
		Dragon(GameObject* pGameObject) :Component(pGameObject) {};
		~Dragon() = default;
		
		// Copy and Move semantics
		Dragon(const Dragon& other)					= delete;
		Dragon& operator=(const Dragon& other)		= delete;
		Dragon(Dragon&& other) noexcept				= delete;
		Dragon& operator=(Dragon&& other) noexcept	= delete;
		
		//---------------------------
		// Public Member Functions
		//---------------------------
		void Init() override;
		void OnDestroy() override;
		void Update() override;

		void Respawn();
		void TransitionToNewLevel(glm::vec2 startPos);
		void NewLevelLoaded();

		void SetPlayerIdx(Player idx);

		bool GetIsLevelLoaded() const { return m_IsNewLevelLoaded; }
		Player GetPlayerIdx() const { return m_PlayerIdx; }
		glm::vec2 GetStartPosition() const { return m_StartPosition; }
		State* GetState() const { return m_pState.get(); }
		
		
	private:
		// Member variables
		bool m_IsNewLevelLoaded{};

		Player m_PlayerIdx{ Player::None };

		glm::vec2 m_StartPosition{};

		std::unique_ptr<State> m_pState{};
		std::unique_ptr<State> m_pAttackState{};

		DelegateHandle m_CollisionHandle{};
		
		//---------------------------
		// Private Member Functions
		//---------------------------
		void OnCollisionNotify(GameObject* pOther);
		
	};
}

