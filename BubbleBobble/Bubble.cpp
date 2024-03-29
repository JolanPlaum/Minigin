//-----------------------------------------------------------------
// Includes
//-----------------------------------------------------------------
#include "Bubble.h"
#include <glm/glm.hpp>
#include "GameObject.h"
#include "Transform.h"
#include "BoxCollider2D.h"
#include "BubbleStates.h"
#include "TimeManager.h"
#include "CSpriteRenderer.h"
#include "EnemyBehaviour.h"

using namespace dae;


//-----------------------------------------------------------------
// Constructors
//-----------------------------------------------------------------
void Bubble::Init()
{
	m_pSprite = GetGameObject()->GetComponent<CSpriteRenderer>();

	m_pCollider = GetGameObject()->GetComponent<BoxCollider2D>();
	m_CollisionHandle = m_pCollider->OnCollision.AddFunction(
		std::bind(&Bubble::OnCollisionNotify, this, std::placeholders::_1));

	if (m_Color.empty()) m_Color = "Green";

	if (m_pState == nullptr) SetState(m_pState, std::make_unique<BubbleStateFloating>(GetGameObject()));

	m_pMoveCommand = std::make_unique<MoveCommand>(GetGameObject(), glm::vec2{ 0, 1 }, 30.f);
}


//-----------------------------------------------------------------
// Destructor
//-----------------------------------------------------------------
void Bubble::OnDestroy()
{
	if (m_CollisionHandle.IsValid())
		m_pCollider->OnCollision.Remove(m_CollisionHandle);

	SetState(m_pState, nullptr);
}


//-----------------------------------------------------------------
// Public Member Functions
//-----------------------------------------------------------------
void Bubble::Update()
{
	if (m_pTrappedEnemy && m_IsNotBeingLaunched == false)
	{
		SetState(m_pState, std::make_unique<BubbleStateFloating>(GetGameObject(), m_pTrappedEnemy->GetName()));
	}

	// Update state
	std::unique_ptr<State> newState = m_pState->Transition();
	if (newState != nullptr)
	{
		SetState(m_pState, std::move(newState));
	}
	m_pState->Update();

	// Early return if bubble is launching
	if (m_IsNotBeingLaunched == false) return;

	// Update movement/hovering
	UpdateMoveCommand();

	// Update enemy animation with custom sec/frame
	if (m_pTrappedEnemy) UpdateEnemyAnimation();
}

void Bubble::Launch(std::unique_ptr<MoveCommand> pCommand)
{
	SetState(m_pState, std::move(std::make_unique<BubbleStateLaunching>(GetGameObject(), std::move(pCommand))));
	m_IsNotBeingLaunched = false;
}

void Bubble::TrapEnemy(GameObject* pEnemy)
{
	m_pTrappedEnemy = pEnemy->GetComponent<EnemyBehaviour>();
	m_pTrappedEnemy->SetTrapped();
	//SetState(m_pState, std::make_unique<BubbleStateFloating>(GetGameObject(), m_pTrappedEnemy->GetName()));
}

void Bubble::EndOfLaunch()
{
	m_IsNotBeingLaunched = true;
}

void Bubble::SetColor(std::string color)
{
	m_Color = color;
}


//-----------------------------------------------------------------
// Private Member Functions
//-----------------------------------------------------------------
void Bubble::OnCollisionNotify(GameObject* pOther)
{
	Boundaries bounds{ m_pCollider->GetBoxBoundaries() };
	Boundaries otherBounds{ pOther->GetComponent<BoxCollider2D>()->GetBoxBoundaries() };

	if (m_IsNotBeingLaunched && pOther->GetTag() == "Friendly")
	{
		if (OverlapPercentageTotal(bounds, otherBounds) > 0.5f)
		{
			// 1. Set this bubble state to popped
			// 2. Set enemy state (if this has an enemy) to death
			// 3. Remove enemy from this bubble
			if (m_pTrappedEnemy) m_pTrappedEnemy->SetDead(GetGameObject()->GetTransform().GetWorldPosition());
			m_pTrappedEnemy = nullptr;

			SetState(m_pState, std::make_unique<BubbleStatePop>(GetGameObject()));
		}
	}
	else if (pOther->GetTag() == "StaticLevel")
	{
		glm::vec2 displacementCorrection{};

		// Top of other bounds
		if (IsBottomCollision(bounds, otherBounds) && OverlapPercentageX(bounds, otherBounds) > 0.2f)
		{
			displacementCorrection.y = otherBounds.y1 - bounds.y2;
		}

		// Left of other bounds
		if (IsLeftCollision(bounds, otherBounds))
		{
			displacementCorrection.x = (otherBounds.x1 - bounds.x2) * 1.25f;
		}
		// Right of other bounds
		else if (IsRightCollision(bounds, otherBounds))
		{
			displacementCorrection.x = (otherBounds.x2 - bounds.x1) * 1.25f;
		}

		displacementCorrection /= glm::abs(GetGameObject()->GetTransform().GetWorldScale());
		auto pos = GetGameObject()->GetTransform().GetLocalPosition();
		GetGameObject()->GetTransform().SetLocalPosition(pos + displacementCorrection);
	}
	else if (pOther->GetTag() == "Roof")
	{
		glm::vec2 correction = (otherBounds.y1 - bounds.y2) / glm::abs(GetGameObject()->GetTransform().GetWorldScale());
		auto pos = GetGameObject()->GetTransform().GetLocalPosition();
		GetGameObject()->GetTransform().SetLocalPosition(pos + correction);

		m_pMoveCommand->FlipDirection();
	}
	else if (m_IsNotBeingLaunched && pOther->GetTag() == "Bubble")
	{
		glm::vec2 direction{ GetGameObject()->GetTransform().GetWorldPosition() - pOther->GetTransform().GetWorldPosition() };
		float bubbleSize{ bounds.x2 - bounds.x1 };
		float distanceToOtherBubble{ glm::clamp(glm::length(direction), 0.001f, bubbleSize) };

		if (distanceToOtherBubble <= 0.001f) return;

		float speed{ 5.f };
		float ratio{ bubbleSize / distanceToOtherBubble };

		auto pos = GetGameObject()->GetTransform().GetLocalPosition();
		GetGameObject()->GetTransform().SetLocalPosition(pos + ratio * speed * TimeManager::GetInstance().GetDeltaTime() * glm::normalize(direction));
	}
}

void Bubble::UpdateEnemyAnimation()
{
	m_EnemyAnimAccuSec += TimeManager::GetInstance().GetDeltaTime();

	if (m_IsEnemyAnimStraight)
	{
		if (m_EnemyAnimAccuSec >= m_EnemyStraightAnimTimer)
		{
			m_EnemyAnimAccuSec -= m_EnemyStraightAnimTimer;
			m_IsEnemyAnimStraight = false;

			if (m_IsEnemyAnimReverse) m_pSprite->SetColIdx(0);
			else m_pSprite->SetColIdx(2);

			m_IsEnemyAnimReverse = !m_IsEnemyAnimReverse;
		}
	}
	else
	{
		if (m_EnemyAnimAccuSec >= m_EnemySideAnimTimer)
		{
			m_EnemyAnimAccuSec -= m_EnemySideAnimTimer;
			m_IsEnemyAnimStraight = true;

			m_pSprite->SetColIdx(1);
		}
	}
}

void Bubble::UpdateMoveCommand()
{
	if (rand() % 4) m_pMoveCommand->Execute();

	if (m_pMoveCommand->GetSpeed() < 0.f)
	{
		m_HoverAccuSec += TimeManager::GetInstance().GetDeltaTime();

		if (m_HoverAccuSec >= m_HoverSwitchTime)
		{
			m_HoverAccuSec = 0.f;
			m_pMoveCommand->FlipDirection();
		}
	}
}

