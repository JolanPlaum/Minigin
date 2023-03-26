//-----------------------------------------------------------------
// Includes
//-----------------------------------------------------------------
#include "MoveCommand.h"
#include "TimeManager.h"
#include "GameObject.h"
#include "Transform.h"

using namespace dae;


//-----------------------------------------------------------------
// Constructors
//-----------------------------------------------------------------
MoveCommand::MoveCommand(GameObject* pGameObject, const glm::vec3& direction, float speed)
	: Command(pGameObject)
	, m_Direction(direction)
	, m_Speed(speed)
{
}


//-----------------------------------------------------------------
// Destructor
//-----------------------------------------------------------------


//-----------------------------------------------------------------
// Public Member Functions
//-----------------------------------------------------------------
void MoveCommand::Execute()
{
	auto pos = GetGameObject()->GetTransform().GetLocalPosition();
	pos += m_Direction * m_Speed * TimeManager::GetInstance().GetDeltaTime();
	GetGameObject()->GetTransform().SetLocalPosition(pos);
}


//-----------------------------------------------------------------
// Private Member Functions
//-----------------------------------------------------------------

