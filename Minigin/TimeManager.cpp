//-----------------------------------------------------------------
// Includes
//-----------------------------------------------------------------
#include "TimeManager.h"

using namespace dae;
using namespace std::chrono;


//-----------------------------------------------------------------
// Constructors
//-----------------------------------------------------------------
TimeManager::TimeManager()
{
	m_PrevTime = high_resolution_clock::now();
}


//-----------------------------------------------------------------
// Public Member Functions
//-----------------------------------------------------------------
void TimeManager::Tick()
{
	//Get the current time
	const auto currentTime = high_resolution_clock::now();

	//Calculate difference between previous and current time
	m_DeltaTime = duration<float>(currentTime - m_PrevTime).count();
	m_DeltaTime = std::min(m_DeltaTime, m_MaxDeltaTime);

	//Calculate fps
	m_FPS = 1.f / m_DeltaTime;

	//Update previous time
	m_PrevTime = currentTime;
}

void TimeManager::Sleep()
{
	//Let the CPU rest if last call was faster than MsPerFrame
	const auto sleepTime = m_PrevTime - high_resolution_clock::now() + milliseconds(m_MsPerFrame);
	std::this_thread::sleep_for(sleepTime);
}


//-----------------------------------------------------------------
// Private Member Functions
//-----------------------------------------------------------------

