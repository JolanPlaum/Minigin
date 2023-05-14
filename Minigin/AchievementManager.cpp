//-----------------------------------------------------------------
// Includes
//-----------------------------------------------------------------
#include "AchievementManager.h"
#include "SteamAchievements.h"
#include "Score.h"

using namespace dae;


//-----------------------------------------------------------------
// Constructors
//-----------------------------------------------------------------
AchievementManager::AchievementManager()
{
	m_ScoreChanged.BindFunction(std::bind(&AchievementManager::OnScoreChanged, this, std::placeholders::_1));
}


//-----------------------------------------------------------------
// Destructor
//-----------------------------------------------------------------
AchievementManager::~AchievementManager()
{
	SetScoreComponent(nullptr);
}


//-----------------------------------------------------------------
// Public Member Functions
//-----------------------------------------------------------------
void AchievementManager::SetScoreComponent(Score* pScore)
{
	if (m_pScore && m_ScoreChanged.IsBound())
		m_pScore->ScoreChanged.Remove(m_ScoreChanged.GetHandle());

	m_pScore = pScore;

	if (m_pScore)
		m_pScore->ScoreChanged.Add(m_ScoreChanged);
}


//-----------------------------------------------------------------
// Private Member Functions
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

