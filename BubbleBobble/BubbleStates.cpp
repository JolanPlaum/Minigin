//-----------------------------------------------------------------
// Includes
//-----------------------------------------------------------------
#include "BubbleStates.h"
#include <glm/vec2.hpp>
#include <functional>
#include "ResourceManager.h"
#include "ServiceLocator.h"
#include "TimeManager.h"
#include "GameObject.h"
#include "Transform.h"
#include "Bubble.h"
#include "CSpriteRenderer.h"
#include "BoxCollider2D.h"

using namespace dae;


//-----------------------------------------------------------------
// BubbleStateLaunching Functions
//-----------------------------------------------------------------
void BubbleStateLaunching::OnEnter()
{
	// Set sprite
	{
		auto pSprite = ResourceManager::GetInstance().LoadSprite("BubbleBobble/Sprites/Bubble/Launching_Anim.png");
		auto pRenderer = GetGameObject()->GetComponentInChildren<CSpriteRenderer>();
		pRenderer->SetSprite(pSprite, 10.f / 60.f);
		pRenderer->SetSettings(SpriteRenderSettings::IterateColumn);
		pRenderer->SetRowIdx(GetGameObject()->GetComponent<Bubble>()->GetColor());
	}

	// Set collision notify
	m_CollisionHandle = GetGameObject()->GetComponent<BoxCollider2D>()->OnCollision.AddFunction(
		std::bind(&BubbleStateLaunching::OnCollisionNotify, this, std::placeholders::_1));

	// Play sound
	Locator::GetSoundSystem().Play("BubbleBobble/Audio/BubbleLaunch.wav", 1.f);
}

void BubbleStateLaunching::OnExit()
{
	if (m_CollisionHandle.IsValid())
		GetGameObject()->GetComponent<BoxCollider2D>()->OnCollision.Remove(m_CollisionHandle);
}

void BubbleStateLaunching::Update()
{
	m_pMoveCommand->Execute();

	m_AccuSec += TimeManager::GetInstance().GetDeltaTime();
}

std::unique_ptr<State> BubbleStateLaunching::Transition()
{
	if (m_AccuSec >= m_LaunchTime) return std::make_unique<BubbleStateFloating>(GetGameObject());
	return nullptr;
}

void BubbleStateLaunching::OnCollisionNotify(GameObject* pOther)
{
	if (pOther->GetTag() == "Enemy")
	{
		GetGameObject()->GetComponent<Bubble>()->TrapEnemy(pOther);
	}
}


//-----------------------------------------------------------------
// BubbleStateFloating Functions
//-----------------------------------------------------------------
void BubbleStateFloating::OnEnter()
{
	// Set sprite
	{
		std::string path{ "BubbleBobble/Sprites/Bubble/" };
		if (!m_EnemyName.empty()) path += m_EnemyName + '_';
		auto pSprite = ResourceManager::GetInstance().LoadSprite(path + "Floating_Anim.png");
		auto pRenderer = GetGameObject()->GetComponentInChildren<CSpriteRenderer>();
		pRenderer->SetSprite(pSprite);
		pRenderer->SetSettings(SpriteRenderSettings::IterateNone);
		pRenderer->SetRowIdx(GetGameObject()->GetComponent<Bubble>()->GetColor());
	}

	// Let Bubble handle collision
	GetGameObject()->GetComponent<Bubble>()->EndOfLaunch();

	// Set Floating time
	float min{ m_MinTime }, max{ m_MaxTime };
	if (!m_EnemyName.empty())
	{
		min = m_MinEnemyTime;
		max = m_MaxEnemyTime;
	}
	m_Timer = min + (static_cast<float>(rand()) / RAND_MAX) * (max - min);
}

void BubbleStateFloating::OnExit()
{
}

void BubbleStateFloating::Update()
{
	m_AccuSec += TimeManager::GetInstance().GetDeltaTime();
}

std::unique_ptr<State> BubbleStateFloating::Transition()
{
	if (m_AccuSec >= m_Timer) return std::make_unique<BubbleStateBreaking>(GetGameObject(), m_EnemyName);
	return nullptr;
}


//-----------------------------------------------------------------
// BubbleStateBreaking Functions
//-----------------------------------------------------------------
void BubbleStateBreaking::OnEnter()
{
	// Set sprite
	{
		std::string path{ "BubbleBobble/Sprites/Bubble/" };
		if (m_EnemyName != "") path += m_EnemyName + '_';
		auto pSprite = ResourceManager::GetInstance().LoadSprite(path + "Breaking_Anim.png");
		m_pRenderer = GetGameObject()->GetComponentInChildren<CSpriteRenderer>();
		m_pRenderer->SetSprite(pSprite, 4.f / 60.f);
		m_pRenderer->SetSettings(SpriteRenderSettings::IterateRow);
		m_pRenderer->Pause(m_FirstFrameTime);
	}

	// Set delegates
	m_AnimationPlay = m_pRenderer->Unpaused.AddFunction(std::bind(&BubbleStateBreaking::OnAnimationPlay, this));
}

void BubbleStateBreaking::OnExit()
{
	// Remove delegates
	if (m_AnimationPlay.IsValid()) m_pRenderer->AnimationLooped.Remove(m_AnimationPlay);
}

void BubbleStateBreaking::Update()
{
	if (m_FrameCount >= 2)
	{
		m_AccuSec += TimeManager::GetInstance().GetDeltaTime();
	}
}

std::unique_ptr<State> BubbleStateBreaking::Transition()
{
	if (m_AccuSec >= m_FlickerTime) return std::make_unique<BubbleStatePop>(GetGameObject());
	return nullptr;
}

void BubbleStateBreaking::OnAnimationPlay()
{
	if (m_FrameCount == 0)
	{
		m_pRenderer->Pause(m_SecondFrameTime);
		++m_FrameCount;
	}
	else if (m_FrameCount == 1)
	{
		++m_FrameCount;
	}
}


//-----------------------------------------------------------------
// BubbleStatePop Functions
//-----------------------------------------------------------------
void BubbleStatePop::OnEnter()
{
	// Set sprite
	{
		auto pSprite = ResourceManager::GetInstance().LoadSprite("BubbleBobble/Sprites/Bubble/Pop_Anim.png");
		auto pRenderer = GetGameObject()->GetComponentInChildren<CSpriteRenderer>();
		pRenderer->SetSettings(SpriteRenderSettings::IterateColumn);
		pRenderer->SetSprite(pSprite, 3.f / 60.f);

		// Set delegates
		m_AnimationEndHandle = pRenderer->AnimationLooped.AddFunction(std::bind(&BubbleStatePop::OnAnimationEnd, this));
	}
}

void BubbleStatePop::OnExit()
{
	if (m_AnimationEndHandle.IsValid())
		GetGameObject()->GetComponentInChildren<CSpriteRenderer>()->AnimationLooped.Remove(m_AnimationEndHandle);
}

void BubbleStatePop::Update()
{
}

std::unique_ptr<State> BubbleStatePop::Transition()
{
	return nullptr;
}

void BubbleStatePop::OnAnimationEnd()
{
	GetGameObject()->Destroy();
}
