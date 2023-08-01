//-----------------------------------------------------------------
// Includes
//-----------------------------------------------------------------
#include "GalagaEnemy.h"
#include "Command.h"
#include "InputManager.h"

using namespace dae;


//-----------------------------------------------------------------
// Constructors
//-----------------------------------------------------------------


//-----------------------------------------------------------------
// Destructor
//-----------------------------------------------------------------
void GalagaEnemy::OnDestroy()
{
	auto& input = InputManager::GetInstance();

	for (Command* pCommand : m_Commands)
	{
		input.RemoveKeyboardCommand(pCommand);
		input.RemoveGamepadCommand(pCommand);
	}
}


//-----------------------------------------------------------------
// Public Member Functions
//-----------------------------------------------------------------
void GalagaEnemy::AddCommand(Command* pCommand)
{
	m_Commands.push_back(pCommand);
}


//-----------------------------------------------------------------
// Private Member Functions
//-----------------------------------------------------------------

