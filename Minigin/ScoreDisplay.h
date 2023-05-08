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
	class ScoreDisplay final : public Component
	{
	public:
		// Constructors and Destructor
		ScoreDisplay(GameObject* pGameObject);
		~ScoreDisplay() = default;
		
		// Copy and Move semantics
		ScoreDisplay(const ScoreDisplay& other)					= delete;
		ScoreDisplay& operator=(const ScoreDisplay& other)		= delete;
		ScoreDisplay(ScoreDisplay&& other) noexcept				= delete;
		ScoreDisplay& operator=(ScoreDisplay&& other) noexcept	= delete;
		
		//---------------------------
		// Public Member Functions
		//---------------------------
		void Init() override;

		void OnScoreChanged(int score);

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

