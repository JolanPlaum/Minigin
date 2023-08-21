#pragma once
// Includes
#include "Component.h"
#include <string>
#include <memory>
#include <glm/vec2.hpp>
#include "State.h"

namespace dae
{
	// Class Forward Declarations
	
	// Class Declaration
	class EnemyBehaviour : public Component
	{
	public:
		// Constructors and Destructor
		EnemyBehaviour(GameObject* pGameObject) :Component(pGameObject) {};
		virtual ~EnemyBehaviour() = default;
		
		// Copy and Move semantics
		EnemyBehaviour(const EnemyBehaviour& other)					= delete;
		EnemyBehaviour& operator=(const EnemyBehaviour& other)		= delete;
		EnemyBehaviour(EnemyBehaviour&& other) noexcept				= delete;
		EnemyBehaviour& operator=(EnemyBehaviour&& other) noexcept	= delete;
		
		//---------------------------
		// Public Member Functions
		//---------------------------
		void Update() override;

		virtual void SetTrapped() = 0;
		virtual void FreeTrapped(glm::vec2 position) = 0;
		virtual void SetDead(glm::vec2 position) = 0;

		std::string GetName() const { return m_Name; }
		State* GetState() const { return m_pState.get(); }
		
		
	private:
		// Member variables
		std::string m_Name{};

		std::unique_ptr<State> m_pState{};

		//---------------------------
		// Private Member Functions
		//---------------------------
		
	protected:
		void SetName(const std::string& name);
		void SetEnemyState(std::unique_ptr<State> pState);
		
	};
}

