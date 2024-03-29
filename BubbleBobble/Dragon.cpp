//-----------------------------------------------------------------
// Includes
//-----------------------------------------------------------------
#include "Dragon.h"
#include "GameObject.h"
#include "Transform.h"
#include "DragonPlayerStates.h"
#include "BoxCollider2D.h"
#include "TimeManager.h"

using namespace dae;


//-----------------------------------------------------------------
// Constructors
//-----------------------------------------------------------------
void Dragon::Init()
{
	m_CollisionHandle = GetGameObject()->GetComponent<BoxCollider2D>()->OnCollision.AddFunction(
		std::bind(&Dragon::OnCollisionNotify, this, std::placeholders::_1));

	if (m_pState == nullptr) m_pState = std::make_unique<DragonPlayerStateIdle>(GetGameObject());
}


//-----------------------------------------------------------------
// Destructor
//-----------------------------------------------------------------
void Dragon::OnDestroy()
{
	if (m_CollisionHandle.IsValid())
		GetGameObject()->GetComponent<BoxCollider2D>()->OnCollision.Remove(m_CollisionHandle);

	SetState(m_pState, nullptr);
}


//-----------------------------------------------------------------
// Public Member Functions
//-----------------------------------------------------------------
void Dragon::Update()
{
	if (m_IsSpawned && m_AccuSec < m_NoHitTime)
	{
		m_AccuSec += TimeManager::GetInstance().GetDeltaTime();
	}

	if (m_pState)
	{
		std::unique_ptr<State> newState = m_pState->Transition();
		if (newState != nullptr)
		{
			SetState(m_pState, std::move(newState));
		}
		m_pState->Update();
	}

	if (m_pAttackState)
	{
		std::unique_ptr<State> newState = m_pAttackState->Transition();
		if (newState != nullptr)
		{
			SetState(m_pAttackState, std::move(newState));
		}
		m_pAttackState->Update();
	}
}

void Dragon::Respawn()
{
	SetState(m_pState, std::make_unique<DragonPlayerStateIdle>(GetGameObject()));
	SetState(m_pAttackState, std::make_unique<DragonPlayerStateAttackReady>(GetGameObject()));

	GetGameObject()->GetTransform().SetLocalPosition(m_StartPosition);

	m_IsSpawned = true;
	Respawned.Notify();
}

void Dragon::TransitionToNewLevel(glm::vec2 startPos)
{
	m_AccuSec = 0.f;
	m_IsSpawned = false;
	m_IsNewLevelLoaded = false;
	m_StartPosition = startPos;
	SetState(m_pState, std::make_unique<DragonPlayerStateWin>(GetGameObject()));
	SetState(m_pAttackState, nullptr);
}
void Dragon::NewLevelLoaded()
{
	m_IsNewLevelLoaded = true;
}

void Dragon::SetPlayerIdx(Player idx)
{
	m_PlayerIdx = idx;
}


//-----------------------------------------------------------------
// Private Member Functions
//-----------------------------------------------------------------
void Dragon::OnCollisionNotify(GameObject* pOther)
{
	if (m_IsSpawned && m_AccuSec >= m_NoHitTime && pOther->GetTag() == "Enemy")
	{
		SetState(m_pState, std::make_unique<DragonPlayerStateDeath>(GetGameObject()));
		SetState(m_pAttackState, nullptr);

		m_IsSpawned = false;
		m_AccuSec = 0.f;
	}
}

