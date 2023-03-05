//-----------------------------------------------------------------
// Includes
//-----------------------------------------------------------------
#include "RotationMovement.h"
#include <glm/glm.hpp>
#include "TimeManager.h"
#include "Transform.h"

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
void RotationMovement::Update()
{
	m_CurrentAngle += TimeManager::GetInstance().GetDeltaTime() * m_RotationSpeed;

	auto x = glm::cos(m_CurrentAngle) * m_Radius;
	auto y = glm::sin(m_CurrentAngle) * m_Radius;

	GetGameObject()->GetTransform().SetLocalPosition(x, y, 0);
}

void RotationMovement::SetRadius(float radius)
{
	m_Radius = radius;
}

void RotationMovement::SetSpeedRadians(float rotationSpeed)
{
	m_RotationSpeed = rotationSpeed;
}

void RotationMovement::SetSpeedDegrees(float rotationSpeed)
{
	SetSpeedRadians(glm::radians(rotationSpeed));
}


//-----------------------------------------------------------------
// Private Member Functions
//-----------------------------------------------------------------

