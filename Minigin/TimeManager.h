#pragma once
// Includes
#include "Singleton.h"
#include <chrono>

namespace dae
{
	// Class Forward Declarations
	
	// Class Declaration
	class TimeManager final : public Singleton<TimeManager>
	{
	public:
		// Constructors and Destructor
		~TimeManager() = default;
		
		// Copy and Move semantics
		TimeManager(const TimeManager& other)					= delete;
		TimeManager& operator=(const TimeManager& other)		= delete;
		TimeManager(TimeManager&& other) noexcept				= delete;
		TimeManager& operator=(TimeManager&& other) noexcept	= delete;
	
		//---------------------------
		// Public Member Functions
		//---------------------------
		void Tick();
		void Sleep();

		float GetDeltaTime() const { return m_DeltaTime; }
		float GetFPS() const { return m_FPS; }
	
	
	private:
		// Member variables
		float m_MaxDeltaTime{ 0.05f };
		float m_DeltaTime{};
		float m_FPS{};

		const int m_MsPerFrame{ 16 };

		std::chrono::high_resolution_clock::time_point m_PrevTime{};
	
		//---------------------------
		// Private Member Functions
		//---------------------------
		friend class Singleton<TimeManager>;
		TimeManager();
	
	};
}

