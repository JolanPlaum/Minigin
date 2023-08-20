#pragma once
#include <glm/vec2.hpp>
#include <glm/common.hpp>
#include <string>
#include "Scene.h"
#include "GameObject.h"
#include "Transform.h"
#include "ResourceManager.h"
#include "BoxCollider2D.h"
#include "CSpriteRenderer.h"
#include "Bubble.h"
#include "MoveCommand.h"

namespace dae
{
	inline GameObject* LaunchedBubble(Scene* pScene, Transform& transform, glm::vec2 direction, std::string color)
	{
		// Create object
		GameObject* pParent = pScene->CreateObject();
		pParent->GetTransform().SetWorldPosition(transform.GetWorldPosition());
		pParent->GetTransform().SetWorldScale(glm::abs(transform.GetWorldScale()));
		pParent->GetTransform().SetWorldRotation(transform.GetWorldRotation());



		// Create object
		GameObject* pGo = pScene->CreateObject();
		pGo->SetTag("Bubble");
		pGo->SetParent(pParent);

		// Add components
		pGo->AddComponent<CSpriteRenderer>();
		pGo->AddComponent<BoxCollider2D>();
		auto pBubble = pGo->AddComponent<Bubble>();

		// Alter components
		pBubble->SetColor(color);
		pBubble->Launch(std::make_unique<MoveCommand>(pGo, direction, 180.f));

		// Return object
		return pGo;
	}
}