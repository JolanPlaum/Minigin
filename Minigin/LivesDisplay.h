#pragma once
// Includes
#include "Component.h"
#include <memory>
#include "DelegateHandle.h"

namespace dae
{
	// Class Forward Declarations
	class CTextTexture;
	class Lives;
	
	// Class Declaration
	class LivesDisplay final : public Component
	{
	public:
		// Constructors and Destructor
		LivesDisplay(GameObject* pGameObject);
		~LivesDisplay();
		
		// Copy and Move semantics
		LivesDisplay(const LivesDisplay& other)					= delete;
		LivesDisplay& operator=(const LivesDisplay& other)		= delete;
		LivesDisplay(LivesDisplay&& other) noexcept				= delete;
		LivesDisplay& operator=(LivesDisplay&& other) noexcept	= delete;
		
		//---------------------------
		// Public Member Functions
		//---------------------------
		void Init() override;		

		void SetLivesComponent(Lives* pLives);
		
		
	private:
		// Member variables
		CTextTexture* m_pText{};
		Lives* m_pLives{};
		DelegateHandle m_PlayerDiedHandle;
		
		//---------------------------
		// Private Member Functions
		//---------------------------
		void OnPlayerDied(int lives);
		
	};
}

