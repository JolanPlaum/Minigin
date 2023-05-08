//-----------------------------------------------------------------
// Includes
//-----------------------------------------------------------------
#include "AchievementManager.h"
#include "SteamAchievements.h"
#include "Observer.h"

using namespace dae;


//-----------------------------------------------------------------
// Constructors
//-----------------------------------------------------------------
AchievementManager::AchievementManager()
	: m_pObserver{ std::make_unique<Observer>() }
{
	m_pObserver->AddEventFunction<int>(EventType::SCORE_CHANGED,
		std::bind(&AchievementManager::OnScoreChanged, this, std::placeholders::_1));
}


//-----------------------------------------------------------------
// Destructor
//-----------------------------------------------------------------


//-----------------------------------------------------------------
// Public Member Functions
//-----------------------------------------------------------------
void AchievementManager::OnScoreChanged(int score)
{
	if (score >= (m_NrWins + 1) * m_WinningScore)
	{
		++m_NrWins;
		if (m_NrWins == 1) Unlock(ACH_WIN_ONE_GAME);
		else if (m_NrWins == 100) Unlock(ACH_WIN_100_GAMES);
	}
}


//-----------------------------------------------------------------
// Private Member Functions
//-----------------------------------------------------------------
void AchievementManager::Unlock(Achievement achievement)
{
	switch (achievement)
	{
	case ACH_WIN_ONE_GAME:
		SteamAchievements::GetInstance().SetAchievement("ACH_WIN_ONE_GAME"); break;
	case ACH_WIN_100_GAMES:
		SteamAchievements::GetInstance().SetAchievement("ACH_WIN_100_GAMES"); break;
	}
}

