#pragma once
#include "Scene.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "CSpriteRenderer.h"
#include "BoxCollider2D.h"

namespace dae
{
	inline GameObject* LevelTileBig(Scene& scene, unsigned int level)
	{
		// Create object
		GameObject* pGo = scene.CreateObject();
		pGo->SetTag("StaticLevel");

		// Add components
		auto pRenderer = pGo->AddComponent<CSpriteRenderer>();
		auto pCollider = pGo->AddComponent<BoxCollider2D>();

		// Alter components
		pRenderer->SetSprite(ResourceManager::GetInstance().LoadSprite("BubbleBobble/Sprites/LevelTilesBig.png"));
		pRenderer->SetSettings(SpriteRenderSettings::IterateNone);
		pRenderer->SetTileIdx(level);
		pCollider->SetSize(pRenderer->GetSize());

		// Return object
		return pGo;
	}

	inline GameObject* LevelTileSmall(Scene& scene, unsigned int level)
	{
		// Create object
		GameObject* pGo = scene.CreateObject();
		pGo->SetTag("Platform");

		// Add components
		auto pRenderer = pGo->AddComponent<CSpriteRenderer>();
		auto pCollider = pGo->AddComponent<BoxCollider2D>();

		// Alter components
		pRenderer->SetSprite(ResourceManager::GetInstance().LoadSprite("BubbleBobble/Sprites/LevelTilesSmall.png"));
		pRenderer->SetSettings(SpriteRenderSettings::IterateNone);
		pRenderer->SetTileIdx(level);
		pCollider->SetSize(pRenderer->GetSize());

		// Return object
		return pGo;
	}
}