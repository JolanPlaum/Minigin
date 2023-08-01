#pragma once
// Includes
#include "Component.h"
#include <vector>

namespace dae
{
	// Class Forward Declarations
	class Command;
	
	// Class Declaration
	class GalagaEnemy final : public Component
	{
	public:
		// Constructors and Destructor
		GalagaEnemy(GameObject* pGameObject) :Component(pGameObject) {};
		~GalagaEnemy() = default;
		
		// Copy and Move semantics
		GalagaEnemy(const GalagaEnemy& other)					= delete;
		GalagaEnemy& operator=(const GalagaEnemy& other)		= delete;
		GalagaEnemy(GalagaEnemy&& other) noexcept				= delete;
		GalagaEnemy& operator=(GalagaEnemy&& other) noexcept	= delete;
		
		//---------------------------
		// Public Member Functions
		//---------------------------
		void OnDestroy() override;

		void AddCommand(Command* pCommand);
		
		
	private:
		// Member variables
		std::vector<Command*> m_Commands{};
		
		//---------------------------
		// Private Member Functions
		//---------------------------
		
	};
}

