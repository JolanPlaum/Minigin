//-----------------------------------------------------------------
// Includes
//-----------------------------------------------------------------
#include "Transform.h"
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
void Transform::ClearDirtyFlags()
{
	ClearDirtyPosition();
	ClearDirtyRotation();
	ClearDirtyScale();
}

void Transform::SetLocalPosition(glm::vec2 pos)
{
	m_LocalPosition = pos;
	SetPositionDirty();
}
void Transform::SetLocalPosition(float x, float y)
{
	SetLocalPosition({ x, y });
}
void Transform::SetLocalRotation(double rot)
{
	m_LocalRotation = rot;
	SetRotationDirty();
}
void Transform::SetLocalScale(glm::vec2 s)
{
	m_LocalScale = s;
	SetScaleDirty();
}
void Transform::SetLocalScale(float x, float y)
{
	SetLocalScale({ x, y });
}
void Transform::SetLocalScale(float s)
{
	SetLocalScale({ s, s });
}

void Transform::SetWorldPosition(glm::vec2 pos)
{
	GameObject* parent = GetGameObject()->GetParent();
	if (parent)
	{
		glm::vec2 localPos = pos - parent->GetTransform().GetWorldPosition();
		double angle = -parent->GetTransform().GetWorldRotation();

		double x = localPos.x * cos(angle) - localPos.y * sin(angle);
		double y = localPos.x * sin(angle) + localPos.y * cos(angle);

		SetLocalPosition(glm::vec2{ x, y } / parent->GetTransform().GetWorldScale());
	}
	else
	{
		SetLocalPosition(pos);
	}
}
void Transform::SetWorldPosition(float x, float y)
{
	SetWorldPosition({ x, y });
}
void Transform::SetWorldRotation(double rot)
{
	SetLocalRotation(rot);

	GameObject* parent = GetGameObject()->GetParent();
	if (parent)	m_LocalRotation -= parent->GetTransform().GetWorldRotation();
}
void Transform::SetWorldScale(glm::vec2 s)
{
	SetLocalScale(s);

	GameObject* parent = GetGameObject()->GetParent();
	if (parent)	m_LocalScale /= parent->GetTransform().GetWorldScale();
}
void Transform::SetWorldScale(float x, float y)
{
	SetWorldScale({ x, y });
}
void Transform::SetWorldScale(float s)
{
	SetWorldScale({ s, s });
}

glm::vec2 Transform::GetLocalPosition()
{
	return m_LocalPosition;
}
double Transform::GetLocalRotation()
{
	return m_LocalRotation;
}
glm::vec2 Transform::GetLocalScale()
{
	return m_LocalScale;
}

glm::vec2 Transform::GetWorldPosition()
{
	ClearDirtyPosition();
	return m_WorldPosition;
}
double Transform::GetWorldRotation()
{
	ClearDirtyRotation();
	return m_WorldRotation;
}
glm::vec2 Transform::GetWorldScale()
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
	GotDirty.Notify();

	for (const auto& child : GetGameObject()->GetChildren())
	{
		child->GetTransform().SetPositionDirty();
	}
}
void Transform::SetRotationDirty()
{
	m_IsRotationDirty = true;
	GotDirty.Notify();

	for (const auto& child : GetGameObject()->GetChildren())
	{
		child->GetTransform().SetRotationDirty();
	}
}
void Transform::SetScaleDirty()
{
	m_IsScaleDirty = true;
	GotDirty.Notify();

	for (const auto& child : GetGameObject()->GetChildren())
	{
		child->GetTransform().SetScaleDirty();
	}
}

void Transform::ClearDirtyPosition()
{
	if (m_IsPositionDirty)
	{
		GameObject* parent = GetGameObject()->GetParent();
		if (parent)
		{
			auto scaledPos = m_LocalPosition * parent->GetTransform().GetWorldScale();
			double angle = parent->GetTransform().GetWorldRotation();

			double x = scaledPos.x * cos(angle) - scaledPos.y * sin(angle);
			double y = scaledPos.x * sin(angle) + scaledPos.y * cos(angle);

			m_WorldPosition = parent->GetTransform().GetWorldPosition() + glm::vec2{ x, y };
		}
		else
		{
			m_WorldPosition = m_LocalPosition;
		}

		m_IsPositionDirty = false;
	}
}
void Transform::ClearDirtyRotation()
{
	if (m_IsRotationDirty)
	{
		m_WorldRotation = m_LocalRotation;

		GameObject* parent = GetGameObject()->GetParent();
		if (parent)	m_WorldRotation += parent->GetTransform().GetWorldRotation();

		m_IsRotationDirty = false;
	}
}
void Transform::ClearDirtyScale()
{
	if (m_IsScaleDirty)
	{
		m_WorldScale = m_LocalScale;

		GameObject* parent = GetGameObject()->GetParent();
		if (parent)	m_WorldScale *= parent->GetTransform().GetWorldScale();

		m_IsScaleDirty = false;
	}
}

