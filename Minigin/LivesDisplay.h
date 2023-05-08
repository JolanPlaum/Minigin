#pragma once
// Includes
#include "Component.h"
#include <memory>

namespace dae
{
	// Class Forward Declarations
	class CTextTexture;
	class Observer;
	
	// Class Declaration
	class LivesDisplay final : public Component
	{
	public:
		// Constructors and Destructor
		LivesDisplay(GameObject* pGameObject);
		~LivesDisplay() = default;
		
		// Copy and Move semantics
		LivesDisplay(const LivesDisplay& other)					= delete;
		LivesDisplay& operator=(const LivesDisplay& other)		= delete;
		LivesDisplay(LivesDisplay&& other) noexcept				= delete;
		LivesDisplay& operator=(LivesDisplay&& other) noexcept	= delete;
		
		//---------------------------
		// Public Member Functions
		//---------------------------
		void Init() override;
		
		void OnPlayerDied(int lives);

		Observer* GetObserver() const { return m_pObserver.get(); }
		
		
	private:
		// Member variables
		CTextTexture* m_pText{};
		const std::unique_ptr<Observer> m_pObserver{};
		
		//---------------------------
		// Private Member Functions
		//---------------------------
		
	};
}

