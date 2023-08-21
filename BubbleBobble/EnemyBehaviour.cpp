//-----------------------------------------------------------------
// Includes
//-----------------------------------------------------------------
#include "EnemyBehaviour.h"
#include "GameObject.h"

using namespace dae;


//-----------------------------------------------------------------
// Constructors
//-----------------------------------------------------------------


//-----------------------------------------------------------------
// Destructor
//-----------------------------------------------------------------


//-----------------------------------------------------------------
// Public Member Functions
//-----------------------------------------------------------------
void EnemyBehaviour::Update()
{
	if (m_pState)
	{
		std::unique_ptr<State> newState = m_pState->Transition();
		if (newState != nullptr)
		{
			SetState(m_pState, std::move(newState));
		}
		m_pState->Update();
	}
}

void EnemyBehaviour::SetName(const std::string& name)
{
	m_Name = name;
}

void EnemyBehaviour::SetEnemyState(std::unique_ptr<State> pState)
{
	SetState(m_pState, std::move(pState));
}


//-----------------------------------------------------------------
// Private Member Functions
//-----------------------------------------------------------------

