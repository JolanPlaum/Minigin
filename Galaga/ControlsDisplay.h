#pragma once
// Includes
#include "Component.h"

namespace dae
{
	// Class Forward Declarations
	
	// Class Declaration
	class ControlsDisplay final : public Component
	{
	public:
		// Constructors and Destructor
		ControlsDisplay(GameObject* pGameObject) :Component(pGameObject) {};
		~ControlsDisplay() = default;
		
		// Copy and Move semantics
		ControlsDisplay(const ControlsDisplay& other)					= delete;
		ControlsDisplay& operator=(const ControlsDisplay& other)		= delete;
		ControlsDisplay(ControlsDisplay&& other) noexcept				= delete;
		ControlsDisplay& operator=(ControlsDisplay&& other) noexcept	= delete;
		
		//---------------------------
		// Public Member Functions
		//---------------------------
		void UpdateGui() override;
		
		
	private:
		// Member variables
		bool m_IsOpen{ true };
		
		//---------------------------
		// Private Member Functions
		//---------------------------
		
	};
}

