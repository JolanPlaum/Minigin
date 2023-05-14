#pragma once
// Includes
#include <memory>
#include "Singleton.h"
#include "Achievements.h"
#include "Delegate.h"

namespace dae
{
	// Class Forward Declarations
	class Score;
	
	// Class Declaration
	class AchievementManager final : public Singleton<AchievementManager>
	{
	public:
		// Constructors and Destructor
		~AchievementManager();
		
		// Copy and Move semantics
		AchievementManager(const AchievementManager& other)					= delete;
		AchievementManager& operator=(const AchievementManager& other)		= delete;
		AchievementManager(AchievementManager&& other) noexcept				= delete;
		AchievementManager& operator=(AchievementManager&& other) noexcept	= delete;
		
		//---------------------------
		// Public Member Functions
		//---------------------------
		void SetScoreComponent(Score* pScore);
		
		
	private:
		// Member variables
		const int m_WinningScore{ 500 };
		int m_NrWins{ 0 };
		Score* m_pScore{};
		Delegate<int> m_ScoreChanged;
		
		//---------------------------
		// Private Member Functions
		//---------------------------
		friend class Singleton<AchievementManager>;
		AchievementManager();

		void OnScoreChanged(int score);
		
		void Unlock(Achievement achievement);
		
	};
}

