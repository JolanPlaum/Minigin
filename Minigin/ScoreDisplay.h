#pragma once
// Includes
#include "Component.h"
#include <memory>
#include "DelegateHandle.h"

namespace dae
{
	// Class Forward Declarations
	class CTextTexture;
	class Score;
	
	// Class Declaration
	class ScoreDisplay final : public Component
	{
	public:
		// Constructors and Destructor
		ScoreDisplay(GameObject* pGameObject);
		~ScoreDisplay();
		
		// Copy and Move semantics
		ScoreDisplay(const ScoreDisplay& other)					= delete;
		ScoreDisplay& operator=(const ScoreDisplay& other)		= delete;
		ScoreDisplay(ScoreDisplay&& other) noexcept				= delete;
		ScoreDisplay& operator=(ScoreDisplay&& other) noexcept	= delete;
		
		//---------------------------
		// Public Member Functions
		//---------------------------
		void Init() override;

		void SetScoreComponent(Score* pScore);
		
		
	private:
		// Member variables
		CTextTexture* m_pText{};
		Score* m_pScore{};
		DelegateHandle m_ScoreChangedHandle;
		
		//---------------------------
		// Private Member Functions
		//---------------------------
		void OnScoreChanged(int score);
		
	};
}

