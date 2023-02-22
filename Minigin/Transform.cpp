//-----------------------------------------------------------------
// Includes
//-----------------------------------------------------------------
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
void Transform::SetPosition(const glm::vec3& pos)
{
	m_Position = pos;
}

void Transform::SetPosition(float x, float y, float z)
{
	SetPosition({ x, y, z });
}

void Transform::SetRotation(const glm::vec3& rot)
{
	m_Rotation = rot;
}

void Transform::SetRotation(float x, float y, float z)
{
	SetRotation({ x, y, z });
}

void Transform::SetScale(const glm::vec3& s)
{
	m_Scale = s;
}

void Transform::SetScale(float x, float y, float z)
{
	SetScale({ x, y, z });
}

void Transform::SetScale(float s)
{
	SetScale({ s, s, s });
}


//-----------------------------------------------------------------
// Private Member Functions
//-----------------------------------------------------------------

