#pragma once
// Includes
#include <steam_api.h>
#include <vector>
#include "Singleton.h"

namespace dae
{
	// Class Forward Declarations
#define _ACH_ID( id, name ) { id, #id, name, "", 0, 0 }
	struct AchievementData
	{
		int m_eAchievementID;
		const char* m_pchAchievementID;
		char m_rgchName[128];
		char m_rgchDescription[256];
		bool m_bAchieved;
		int m_iIconImage;
	};
	
	// Class Declaration
	class SteamAchievements final : public Singleton<SteamAchievements>
	{
	public:
		// Constructors and Destructor
		~SteamAchievements();
		
		// Copy and Move semantics
		SteamAchievements(const SteamAchievements& other)					= delete;
		SteamAchievements& operator=(const SteamAchievements& other)		= delete;
		SteamAchievements(SteamAchievements&& other) noexcept				= delete;
		SteamAchievements& operator=(SteamAchievements&& other) noexcept	= delete;
		
		//---------------------------
		// Public Member Functions
		//---------------------------
		void Init(std::vector<AchievementData> achievements);

		bool RequestStats();
		bool SetAchievement(const char* ID);

		STEAM_CALLBACK(SteamAchievements, OnUserStatsReceived, UserStatsReceived_t, m_CallbackUserStatsReceived);
		STEAM_CALLBACK(SteamAchievements, OnUserStatsStored, UserStatsStored_t, m_CallbackUserStatsStored);
		STEAM_CALLBACK(SteamAchievements, OnAchievementStored, UserAchievementStored_t, m_CallbackAchievementStored);
		
		
	private:
		// Member variables
		uint64 m_iAppID; // Our current AppID
		std::vector<AchievementData> m_Achievements; // Achievements data
		bool m_bInitialized; // Have we called Request stats and received the callback?
		
		//---------------------------
		// Private Member Functions
		//---------------------------
		friend class Singleton<SteamAchievements>;
		SteamAchievements();
		
	};
}

