#pragma once
#include "Scene.h"
#include "GameObject.h"
#include "CSpriteRenderer.h"
#include "BoxCollider2D.h"
#include "KeepSpriteSheetCentered.h"
#include "EntityCollision.h"
#include "ZenChan.h"

namespace dae
{
	inline GameObject* ZenChanPrefab(Scene* pScene)
	{
		// Create object
		GameObject* pGo = pScene->CreateObject();
		pGo->SetTag("Enemy");

		// Visuals
		{
			GameObject* pVisuals = pScene->CreateObject();
			pVisuals->SetParent(pGo);

			pVisuals->AddComponent<KeepSpriteSheetCentered>();
			pVisuals->AddComponent<CSpriteRenderer>();
		}

		// Add components
		pGo->AddComponent<EntityCollision>();
		auto pCollider = pGo->AddComponent<BoxCollider2D>();
		pGo->AddComponent<ZenChan>();

		// Alter components
		pCollider->SetSize(glm::vec2{ 12, 12 });
		pCollider->SetOffset(glm::vec2{ -6.f, 0.f });

		// Return object
		return pGo;
	}
}