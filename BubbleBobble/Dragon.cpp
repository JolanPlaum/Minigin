//-----------------------------------------------------------------
// Includes
//-----------------------------------------------------------------
#include "Dragon.h"
#include "GameObject.h"
#include "DragonPlayerStates.h"
#include "BoxCollider2D.h"

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
	std::unique_ptr<State> newState = m_pState->Transition();
	if (newState != nullptr)
	{
		SetState(m_pState, std::move(newState));
	}
	m_pState->Update();
}

void Dragon::TransitionToNewLevel(glm::vec2 startPos)
{
	m_IsNewLevelLoaded = false;
	m_StartPosition = startPos;
	SetState(m_pState, std::make_unique<DragonPlayerStateWin>(GetGameObject()));
	//todo: set attack state to immobilized
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
void Dragon::OnCollisionNotify(GameObject*)
{
}

