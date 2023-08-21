#pragma once
#include "Scene.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "CSpriteRenderer.h"
#include "BoxCollider2D.h"
#include "KeepSpriteSheetCentered.h"
#include "EntityCollision.h"
#include "Dragon.h"
#include "Lives.h"
#include "Score.h"

namespace dae
{
	inline GameObject* BobPrefab(Scene* pScene)
	{
		// Create object
		GameObject* pGo = pScene->CreateObject();
		pGo->SetTag("Friendly");

		// Visuals
		{
			GameObject* pVisuals = pScene->CreateObject();
			pVisuals->SetParent(pGo);

			pVisuals->AddComponent<KeepSpriteSheetCentered>();
			auto pRenderer = pVisuals->AddComponent<CSpriteRenderer>();

			pRenderer->SetSprite(ResourceManager::GetInstance().LoadSprite("BubbleBobble/Sprites/Dragon/Idle_Anim.png"));
			pRenderer->SetSettings(SpriteRenderSettings::IterateColumn);
			pRenderer->SetRowIdx(0);
		}

		// Add components
		pGo->AddComponent<EntityCollision>();
		auto pCollider = pGo->AddComponent<BoxCollider2D>();
		auto pDragon = pGo->AddComponent<Dragon>();
		pGo->AddComponent<Lives>();
		pGo->AddComponent<Score>();

		// Alter components
		pCollider->SetSize(glm::vec2{ 12, 12 });
		pCollider->SetOffset(glm::vec2{ -6.f, 0.f });
		pDragon->SetPlayerIdx(Player::One);

		// Return object
		return pGo;
	}

	inline GameObject* BubPrefab(Scene* pScene)
	{
		// Create object
		GameObject* pGo = pScene->CreateObject();
		pGo->SetTag("Friendly");

		// Visuals
		{
			GameObject* pVisuals = pScene->CreateObject();
			pVisuals->SetParent(pGo);

			pVisuals->AddComponent<KeepSpriteSheetCentered>();
			auto pRenderer = pVisuals->AddComponent<CSpriteRenderer>();

			pRenderer->SetSprite(ResourceManager::GetInstance().LoadSprite("BubbleBobble/Sprites/Dragon/Idle_Anim.png"));
			pRenderer->SetSettings(SpriteRenderSettings::IterateColumn);
			pRenderer->SetRowIdx(1);
		}

		// Add components
		pGo->AddComponent<EntityCollision>();
		auto pCollider = pGo->AddComponent<BoxCollider2D>();
		auto pDragon = pGo->AddComponent<Dragon>();
		pGo->AddComponent<Lives>();
		pGo->AddComponent<Score>();

		// Alter components
		pCollider->SetSize(glm::vec2{ 12, 12 });
		pCollider->SetOffset(glm::vec2{ -6.f, 0.f });
		pDragon->SetPlayerIdx(Player::Two);

		// Return object
		return pGo;
	}
}