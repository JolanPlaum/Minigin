//-----------------------------------------------------------------
// Includes
//-----------------------------------------------------------------
#include "SteamAchievements.h"

using namespace dae;


//-----------------------------------------------------------------
// Constructors
//-----------------------------------------------------------------
SteamAchievements::SteamAchievements()
    : m_iAppID{ 0 }
    , m_Achievements{ }
    , m_bInitialized{ false }
    , m_CallbackUserStatsReceived{ this, &SteamAchievements::OnUserStatsReceived }
    , m_CallbackUserStatsStored{ this, &SteamAchievements::OnUserStatsStored }
    , m_CallbackAchievementStored{ this, &SteamAchievements::OnAchievementStored }
{
}


//-----------------------------------------------------------------
// Destructor
//-----------------------------------------------------------------
SteamAchievements::~SteamAchievements()
{
}

void SteamAchievements::Init(std::vector<AchievementData> achievements)
{
	m_Achievements = achievements;

    m_iAppID = SteamUtils()->GetAppID();
    RequestStats();
}


//-----------------------------------------------------------------
// Public Member Functions
//-----------------------------------------------------------------
bool SteamAchievements::RequestStats()
{
	// Is Steam loaded? If not we can't get stats.
	if (NULL == SteamUserStats() || NULL == SteamUser())
	{
		return false;
	}

	// Is the user logged on?  If not we can't get stats.
	if (!SteamUser()->BLoggedOn())
	{
		return false;
	}

	// Request user stats.
	return SteamUserStats()->RequestCurrentStats();
}

bool SteamAchievements::SetAchievement(const char* ID)
{
	// Have we received a call back from Steam yet?
	if (m_bInitialized)
	{
		SteamUserStats()->SetAchievement(ID);
		return SteamUserStats()->StoreStats();
	}

	// If not then we can't set achievements yet
	return false;
}

void SteamAchievements::OnUserStatsReceived(UserStatsReceived_t* pCallback)
{
	// we may get callbacks for other games' stats arriving, ignore them
	if (m_iAppID == pCallback->m_nGameID)
	{
		if (k_EResultOK == pCallback->m_eResult)
		{
			//OutputDebugString("Received stats and achievements from Steam\n");
			m_bInitialized = true;

			// load achievements
			for (AchievementData& ach : m_Achievements)
			{
				SteamUserStats()->GetAchievement(ach.m_pchAchievementID, &ach.m_bAchieved);
				_snprintf_s(ach.m_rgchName, sizeof(ach.m_rgchName), "%s",
					SteamUserStats()->GetAchievementDisplayAttribute(ach.m_pchAchievementID,
						"name"));
				_snprintf_s(ach.m_rgchDescription, sizeof(ach.m_rgchDescription), "%s",
					SteamUserStats()->GetAchievementDisplayAttribute(ach.m_pchAchievementID,
						"desc"));
			}
		}
		//else
		//{
		//	char buffer[128];
		//	_snprintf(buffer, 128, "RequestStats - failed, %d\n", pCallback->m_eResult);
		//	OutputDebugString(buffer);
		//}
	}
}

void SteamAchievements::OnUserStatsStored(UserStatsStored_t*)
{
	// we may get callbacks for other games' stats arriving, ignore them
	//if (m_iAppID == pCallback->m_nGameID)
	//{
	//	if (k_EResultOK == pCallback->m_eResult)
	//	{
	//		OutputDebugString("Stored stats for Steam\n");
	//	}
	//	else
	//	{
	//		char buffer[128];
	//		_snprintf(buffer, 128, "StatsStored - failed, %d\n", pCallback->m_eResult);
	//		OutputDebugString(buffer);
	//	}
	//}
}

void SteamAchievements::OnAchievementStored(UserAchievementStored_t*)
{
	// we may get callbacks for other games' stats arriving, ignore them
	//if (m_iAppID == pCallback->m_nGameID)
	//{
	//	OutputDebugString("Stored Achievement for Steam\n");
	//}
}


//-----------------------------------------------------------------
// Private Member Functions
//-----------------------------------------------------------------

