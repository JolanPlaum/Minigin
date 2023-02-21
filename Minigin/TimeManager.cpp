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
void TimeManager::Update()
{
	//Get the current time
	const auto currentTime = high_resolution_clock::now();

	//Calculate difference between previous and current time
	m_DeltaTime = duration<float>(currentTime - m_PrevTime).count();

	//Calculate fps
	m_FPS = 1.f / m_DeltaTime;

	//Update previous time
	m_PrevTime = currentTime;
}

void TimeManager::Sleep()
{
	//Let the CPU rest if last call was faster than MsPerFrame
	const auto sleepTime = duration<float>(m_PrevTime - high_resolution_clock::now() + milliseconds(m_MsPerFrame));
	if (sleepTime.count() > 0.f)
	{
		std::this_thread::sleep_for(sleepTime);
	}
}


//-----------------------------------------------------------------
// Private Member Functions
//-----------------------------------------------------------------

