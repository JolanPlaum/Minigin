//-----------------------------------------------------------------
// Includes
//-----------------------------------------------------------------
#include "MoveCommand.h"
#include <glm/geometric.hpp>
#include "TimeManager.h"
#include "GameObject.h"
#include "Transform.h"

using namespace dae;


//-----------------------------------------------------------------
// Constructors
//-----------------------------------------------------------------
MoveCommand::MoveCommand(GameObject* pGameObject, glm::vec2 direction, float speed)
	: GameObjectCommand(pGameObject)
	, m_Direction(glm::normalize(direction))
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

void MoveCommand::FlipDirection()
{
	m_Speed *= -1;
}


//-----------------------------------------------------------------
// Private Member Functions
//-----------------------------------------------------------------

