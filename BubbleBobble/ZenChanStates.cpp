//-----------------------------------------------------------------
// Includes
//-----------------------------------------------------------------
#include "ZenChanStates.h"
#include <glm/common.hpp>
#include "ResourceManager.h"
#include "TimeManager.h"
#include "GameObject.h"
#include "Transform.h"
#include "CSpriteRenderer.h"
#include "EntityCollision.h"
#include "BoxCollider2D.h"
#include "Scene.h"
#include "KeepSpriteSheetCentered.h"
#include "Item.h"

using namespace dae;


//-----------------------------------------------------------------
// ZenChanWaitForJump Functions
//-----------------------------------------------------------------
void ZenChanWaitForJump::OnEnter()
{
	// Set sprite
	{
		auto pSprite = ResourceManager::GetInstance().LoadSprite("BubbleBobble/Sprites/Enemies/ZenChan_Anim.png");
		m_pRenderer = GetGameObject()->GetComponentInChildren<CSpriteRenderer>();
		m_pRenderer->SetSprite(pSprite);
		
		auto& trans = m_pRenderer->GetGameObject()->GetTransform();
		trans.SetLocalScale(-trans.GetLocalScale().x, trans.GetLocalScale().y);
	}
}

void ZenChanWaitForJump::OnExit()
{
}

void ZenChanWaitForJump::Update()
{
	m_AccuSec += TimeManager::GetInstance().GetDeltaTime();

	if (!m_IsFlipped && m_AccuSec >= (m_WaitTimer / 2.f))
	{
		m_IsFlipped = true;
		
		auto& trans = m_pRenderer->GetGameObject()->GetTransform();
		trans.SetLocalScale(-trans.GetLocalScale().x, trans.GetLocalScale().y);
	}
}

std::unique_ptr<State> ZenChanWaitForJump::Transition()
{
	if (m_AccuSec >= m_WaitTimer) return std::make_unique<ZenChanJump>(GetGameObject());
	return nullptr;
}


//-----------------------------------------------------------------
// ZenChanJump Functions
//-----------------------------------------------------------------
void ZenChanJump::OnEnter()
{
	// Set sprite
	{
		auto pSprite = ResourceManager::GetInstance().LoadSprite("BubbleBobble/Sprites/Enemies/ZenChan_Anim.png");
		auto pRenderer = GetGameObject()->GetComponentInChildren<CSpriteRenderer>();
		pRenderer->SetSprite(pSprite, 6.f / 60.f);
	}

	// Set upwards movement
	m_pMoveCommand = std::make_unique<MoveCommand>(GetGameObject(), glm::vec2{ 0, 1 }, 100.f);
}

void ZenChanJump::OnExit()
{
}

void ZenChanJump::Update()
{
	m_AccuSec += TimeManager::GetInstance().GetDeltaTime();
	m_pMoveCommand->Execute();
}

std::unique_ptr<State> ZenChanJump::Transition()
{
	if (m_AccuSec >= m_JumpTime) return std::make_unique<ZenChanFall>(GetGameObject());
	return nullptr;
}


//-----------------------------------------------------------------
// ZenChanFall Functions
//-----------------------------------------------------------------
void ZenChanFall::OnEnter()
{
	// Set sprite
	{
		auto pSprite = ResourceManager::GetInstance().LoadSprite("BubbleBobble/Sprites/Enemies/ZenChan_Anim.png");
		auto pRenderer = GetGameObject()->GetComponentInChildren<CSpriteRenderer>();
		pRenderer->SetSprite(pSprite, 6.f / 60.f);
	}

	// Get Entity collision
	m_pEntityCollision = GetGameObject()->GetComponent<EntityCollision>();

	// Set downwards movement
	m_pMoveCommand = std::make_unique<MoveCommand>(GetGameObject(), glm::vec2{ 0, -1 }, 80.f);
}

void ZenChanFall::OnExit()
{
}

void ZenChanFall::Update()
{
	m_pMoveCommand->Execute();
}

std::unique_ptr<State> ZenChanFall::Transition()
{
	if (m_pEntityCollision->IsGoingDown()) return nullptr;
	return std::make_unique<ZenChanWalk>(GetGameObject());
}


//-----------------------------------------------------------------
// ZenChanWalk Functions
//-----------------------------------------------------------------
void ZenChanWalk::OnEnter()
{
	// Set sprite
	{
		auto pSprite = ResourceManager::GetInstance().LoadSprite("BubbleBobble/Sprites/Enemies/ZenChan_Anim.png");
		auto pRenderer = GetGameObject()->GetComponentInChildren<CSpriteRenderer>();
		pRenderer->SetSprite(pSprite, 6.f / 60.f);
	}

	// Get Entity collision
	m_pEntityCollision = GetGameObject()->GetComponent<EntityCollision>();

	// Set downwards movement
	m_pMoveCommand = std::make_unique<MoveCommand>(GetGameObject(), glm::vec2{ (rand() % 2) ? -1 : 1, -1}, 80.f);

	// Set Walking time
	m_Timer = m_MinTime + (static_cast<float>(rand()) / RAND_MAX) * (m_MaxTime - m_MinTime);
}

void ZenChanWalk::OnExit()
{
}

void ZenChanWalk::Update()
{
	m_AccuSec += TimeManager::GetInstance().GetDeltaTime();

	m_pMoveCommand->Execute();
}

std::unique_ptr<State> ZenChanWalk::Transition()
{
	if (m_pEntityCollision->IsGoingDown()) return std::make_unique<ZenChanFall>(GetGameObject());
	if (m_AccuSec >= m_Timer) return std::make_unique<ZenChanWaitForJump>(GetGameObject());
	return nullptr;
}


//-----------------------------------------------------------------
// ZenChanTrapped Functions
//-----------------------------------------------------------------
void ZenChanTrapped::OnEnter()
{
	// Set sprite
	{
		auto pRenderer = GetGameObject()->GetComponentInChildren<CSpriteRenderer>();
		pRenderer->SetSprite(nullptr);
	}

	GetGameObject()->GetComponent<BoxCollider2D>()->Destroy();
}

void ZenChanTrapped::OnExit()
{
	auto pCollider = GetGameObject()->AddComponent<BoxCollider2D>();

	pCollider->SetSize(glm::vec2{ 12, 12 });
	pCollider->SetOffset(glm::vec2{ -6.f, 0.f });
}

void ZenChanTrapped::Update()
{
}

std::unique_ptr<State> ZenChanTrapped::Transition()
{
	return nullptr;
}


//-----------------------------------------------------------------
// ZenChanDeath Functions
//-----------------------------------------------------------------
void ZenChanDeath::OnEnter()
{
	// Set sprite
	{
		auto pSprite = ResourceManager::GetInstance().LoadSprite("BubbleBobble/Sprites/Enemies/ZenChan_Death_Anim.png");
		auto pRenderer = GetGameObject()->GetComponentInChildren<CSpriteRenderer>();
		pRenderer->SetSprite(pSprite, 4.f / 60.f);
	}

	GetGameObject()->GetComponent<BoxCollider2D>()->Destroy();
}

void ZenChanDeath::OnExit()
{
	auto& transform = GetGameObject()->GetComponentInChildren<CSpriteRenderer>()->GetGameObject()->GetTransform();

	// Create object
	GameObject* pParent = GetGameObject()->GetScene()->CreateObject();
	pParent->GetTransform().SetWorldPosition(transform.GetWorldPosition());
	pParent->GetTransform().SetWorldScale(glm::abs(transform.GetWorldScale()));
	pParent->GetTransform().SetWorldRotation(transform.GetWorldRotation());


	auto go = GetGameObject()->GetScene()->CreateObject();
	go->SetTag("Item");
	go->SetParent(pParent);
	auto renderer = go->AddComponent<CSpriteRenderer>();
	go->AddComponent<BoxCollider2D>();
	auto item = go->AddComponent<Item>();
	item->SetName("Watermelon");

	auto pSprite = ResourceManager::GetInstance().LoadSprite("BubbleBobble/Sprites/Items.png");
	renderer->SetSprite(pSprite);
	renderer->SetSettings(SpriteRenderSettings::IterateNone);
	renderer->SetTileIdx(item->GetName());
}

void ZenChanDeath::Update()
{
	m_AccuSec += TimeManager::GetInstance().GetDeltaTime();

	if (m_AccuSec >= m_DeathAnimTime)
	{
		GetGameObject()->Destroy();
	}
}

std::unique_ptr<State> ZenChanDeath::Transition()
{
	return nullptr;
}