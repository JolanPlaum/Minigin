//-----------------------------------------------------------------
// Includes
//-----------------------------------------------------------------
#include "Transform.h"
#include <algorithm>

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
void Transform::ClearDirtyFlags()
{
	ClearDirtyPosition();
	ClearDirtyRotation();
	ClearDirtyScale();
}

void Transform::SetLocalPosition(const glm::vec3& pos)
{
	m_LocalPosition = pos;
	SetPositionDirty();
}
void Transform::SetLocalPosition(float x, float y, float z)
{
	SetLocalPosition({ x, y, z });
}
void Transform::SetLocalRotation(const glm::vec3& rot)
{
	m_LocalRotation = rot;
	SetRotationDirty();
}
void Transform::SetLocalRotation(float x, float y, float z)
{
	SetLocalRotation({ x, y, z });
}
void Transform::SetLocalScale(const glm::vec3& s)
{
	m_LocalScale = s;
	SetScaleDirty();
}
void Transform::SetLocalScale(float x, float y, float z)
{
	SetLocalScale({ x, y, z });
}
void Transform::SetLocalScale(float s)
{
	SetLocalScale({ s, s, s });
}

void Transform::SetWorldPosition(const glm::vec3& pos)
{
	SetLocalPosition(pos);

	GameObject* parent = GetGameObject()->GetParent().lock().get();
	if (parent)	m_LocalPosition -= parent->GetTransform().GetWorldPosition();
}
void Transform::SetWorldPosition(float x, float y, float z)
{
	SetWorldPosition({ x, y, z });
}
void Transform::SetWorldRotation(const glm::vec3& rot)
{
	SetLocalRotation(rot);

	GameObject* parent = GetGameObject()->GetParent().lock().get();
	if (parent)	m_LocalRotation -= parent->GetTransform().GetWorldRotation();
}
void Transform::SetWorldRotation(float x, float y, float z)
{
	SetWorldRotation({ x, y, z });
}
void Transform::SetWorldScale(const glm::vec3& s)
{
	SetLocalScale(s);

	GameObject* parent = GetGameObject()->GetParent().lock().get();
	if (parent)	m_LocalScale /= parent->GetTransform().GetWorldScale();
}
void Transform::SetWorldScale(float x, float y, float z)
{
	SetWorldScale({ x, y, z });
}
void Transform::SetWorldScale(float s)
{
	SetWorldScale({ s, s, s });
}

const glm::vec3& Transform::GetLocalPosition()
{
	return m_LocalPosition;
}
const glm::vec3& Transform::GetLocalRotation()
{
	return m_LocalRotation;
}
const glm::vec3& Transform::GetLocalScale()
{
	return m_LocalScale;
}

const glm::vec3& Transform::GetWorldPosition()
{
	ClearDirtyPosition();
	return m_WorldPosition;
}
const glm::vec3& Transform::GetWorldRotation()
{
	ClearDirtyRotation();
	return m_WorldRotation;
}
const glm::vec3& Transform::GetWorldScale()
{
	ClearDirtyScale();
	return m_WorldScale;
}


//-----------------------------------------------------------------
// Private Member Functions
//-----------------------------------------------------------------
void Transform::SetPositionDirty()
{
	m_IsPositionDirty = true;

	for (const auto& child : GetGameObject()->GetChildren())
	{
		child->GetTransform().SetPositionDirty();
	}
}
void Transform::SetRotationDirty()
{
	m_IsRotationDirty = true;

	for (const auto& child : GetGameObject()->GetChildren())
	{
		child->GetTransform().SetRotationDirty();
	}
}
void Transform::SetScaleDirty()
{
	m_IsScaleDirty = true;

	for (const auto& child : GetGameObject()->GetChildren())
	{
		child->GetTransform().SetScaleDirty();
	}
}

void Transform::ClearDirtyPosition()
{
	if (m_IsPositionDirty)
	{
		m_WorldPosition = m_LocalPosition;

		GameObject* parent = GetGameObject()->GetParent().lock().get();
		if (parent)	m_WorldPosition += parent->GetTransform().GetWorldPosition();

		m_IsPositionDirty = false;
	}
}
void Transform::ClearDirtyRotation()
{
	if (m_IsRotationDirty)
	{
		m_WorldRotation = m_LocalRotation;

		GameObject* parent = GetGameObject()->GetParent().lock().get();
		if (parent)	m_WorldRotation += parent->GetTransform().GetWorldRotation();

		m_IsRotationDirty = false;
	}
}
void Transform::ClearDirtyScale()
{
	if (m_IsScaleDirty)
	{
		m_WorldScale = m_LocalScale;

		GameObject* parent = GetGameObject()->GetParent().lock().get();
		if (parent)	m_WorldScale *= parent->GetTransform().GetWorldScale();

		m_IsScaleDirty = false;
	}
}

