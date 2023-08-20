//-----------------------------------------------------------------
// Includes
//-----------------------------------------------------------------
#include "EntityCollision.h"
#include <glm/common.hpp>
#include "GameObject.h"
#include "Transform.h"
#include "BoxCollider2D.h"

using namespace dae;


//-----------------------------------------------------------------
// Constructors
//-----------------------------------------------------------------
void EntityCollision::Init()
{
	m_pCollider = GetGameObject()->GetComponent<BoxCollider2D>();
	m_CollisionHandle = m_pCollider->OnCollision.AddFunction(
		std::bind(&EntityCollision::OnCollisionNotify, this, std::placeholders::_1));

	m_CurrentPosition = GetGameObject()->GetTransform().GetWorldPosition();
}


//-----------------------------------------------------------------
// Destructor
//-----------------------------------------------------------------
void EntityCollision::OnDestroy()
{
	if (m_CollisionHandle.IsValid())
		GetGameObject()->GetComponent<BoxCollider2D>()->OnCollision.Remove(m_CollisionHandle);
}


//-----------------------------------------------------------------
// Public Member Functions
//-----------------------------------------------------------------
void EntityCollision::Update()
{
	// Update positions
	m_PreviousPosition = m_CurrentPosition;
	m_CurrentPosition = GetGameObject()->GetTransform().GetWorldPosition();

	// Update direction booleans
	m_IsGoingLeft = m_CurrentPosition.x < m_PreviousPosition.x;
	m_IsGoingRight = m_CurrentPosition.x > m_PreviousPosition.x;

	m_IsGoingDown = m_CurrentPosition.y < m_PreviousPosition.y;
	m_IsGoingUp = m_CurrentPosition.y > m_PreviousPosition.y;

	// Update platform boolean helper
	m_WasInPlatform = m_IsInPlatform;
	m_IsInPlatform = false;
}

void EntityCollision::SetStaticLevelCollision(bool isCollision)
{
	m_IsCollisionStatic = isCollision;
}

void EntityCollision::SetPlatformCollision(bool isCollision)
{
	m_IsCollisionPlatform = isCollision;
}


//-----------------------------------------------------------------
// Private Member Functions
//-----------------------------------------------------------------
void EntityCollision::OnCollisionNotify(GameObject* pOther)
{
	Boundaries bounds{ m_pCollider->GetBoxBoundaries() };
	Boundaries otherBounds{ pOther->GetComponent<BoxCollider2D>()->GetBoxBoundaries() };

	glm::vec2 displacementCorrection{};
	const float overlappingX{ 0.2f }, overlappingY{ 0.4f };

	if (m_IsCollisionStatic && pOther->GetTag() == "StaticLevel")
	{
		// Left of other bounds
		if (IsLeftCollision(bounds, otherBounds) && OverlapPercentageY(bounds, otherBounds) > overlappingY)
		{
			displacementCorrection.x = otherBounds.x1 - bounds.x2;
		}
		// Right of other bounds
		else if (IsRightCollision(bounds, otherBounds) && OverlapPercentageY(bounds, otherBounds) > overlappingY)
		{
			displacementCorrection.x = otherBounds.x2 - bounds.x1;
		}

		// Under other bounds
		if (IsBottomCollision(bounds, otherBounds) && OverlapPercentageX(bounds, otherBounds) > overlappingX)
		{
			displacementCorrection.y = otherBounds.y1 - bounds.y2;
		}
		// Top of other bounds
		else if (IsTopCollision(bounds, otherBounds) && OverlapPercentageX(bounds, otherBounds) > overlappingX)
		{
			displacementCorrection.y = otherBounds.y2 - bounds.y1;
		}
	}
	else if (m_IsCollisionPlatform && pOther->GetTag() == "Platform")
	{
		if (m_WasInPlatform)
		{
			if (OverlapPercentageTotal(bounds, otherBounds) > 0.10f) m_IsInPlatform = true;
		}
		else
		{
			if (m_IsGoingUp)
			{
				if (OverlapPercentageTotal(bounds, otherBounds) > 0.10f) m_IsInPlatform = true;
			}
			else
			{
				// Top of other bounds
				if (IsTopCollision(bounds, otherBounds) && OverlapPercentageX(bounds, otherBounds) > overlappingX)
				{
					displacementCorrection.y = otherBounds.y2 - bounds.y1;
				}

				// Left of other bounds
				if (IsLeftCollision(bounds, otherBounds) && OverlapPercentageY(bounds, otherBounds) > overlappingY)
				{
					displacementCorrection.x = otherBounds.x1 - bounds.x2;
				}
				// Right of other bounds
				else if (IsRightCollision(bounds, otherBounds) && OverlapPercentageY(bounds, otherBounds) > overlappingY)
				{
					displacementCorrection.x = otherBounds.x2 - bounds.x1;
				}
			}
		}
	}

	if (displacementCorrection == glm::vec2{ 0,0 }) return;

	displacementCorrection /= glm::abs(GetGameObject()->GetTransform().GetWorldScale());
	auto pos = GetGameObject()->GetTransform().GetLocalPosition();
	GetGameObject()->GetTransform().SetLocalPosition(pos + displacementCorrection);

	//todo: remove this once lateUpdate has been implemented
	m_CurrentPosition = GetGameObject()->GetTransform().GetWorldPosition();
}

