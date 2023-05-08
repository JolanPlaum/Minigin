#pragma once
// Includes
#include <memory>
#include "Singleton.h"
#include "Achievements.h"

namespace dae
{
	// Class Forward Declarations
	class Observer;
	
	// Class Declaration
	class AchievementManager final : public Singleton<AchievementManager>
	{
	public:
		// Constructors and Destructor
		~AchievementManager() = default;
		
		// Copy and Move semantics
		AchievementManager(const AchievementManager& other)					= delete;
		AchievementManager& operator=(const AchievementManager& other)		= delete;
		AchievementManager(AchievementManager&& other) noexcept				= delete;
		AchievementManager& operator=(AchievementManager&& other) noexcept	= delete;
		
		//---------------------------
		// Public Member Functions
		//---------------------------
		void OnScoreChanged(int score);
		
		Observer* GetObserver() const { return m_pObserver.get(); }
		
		
	private:
		// Member variables
		const std::unique_ptr<Observer> m_pObserver{};

		const int m_WinningScore{ 500 };
		int m_NrWins{ 0 };
		
		//---------------------------
		// Private Member Functions
		//---------------------------
		friend class Singleton<AchievementManager>;
		AchievementManager();

		void Unlock(Achievement achievement);
		
	};
}

