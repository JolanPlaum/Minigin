#pragma once
#include "Scene.h"
#include "GameObject.h"
#include "Transform.h"
#include "CTextTexture.h"
#include "CTextureRenderer.h"
#include "ResourceManager.h"

namespace dae
{
	namespace AssignmentBackground
	{
		void LoadScene(Scene& scene)
		{
			//Background
			auto go = std::make_shared<GameObject>();
			auto textureRenderer = go->AddComponent<CTextureRenderer>();

			textureRenderer->SetTexture(ResourceManager::GetInstance().LoadTexture("background.tga"));
			scene.Add(go);


			//DAE logo
			go = std::make_shared<GameObject>();
			textureRenderer = go->AddComponent<CTextureRenderer>();

			textureRenderer->SetTexture(ResourceManager::GetInstance().LoadTexture("logo.tga"));
			go->GetTransform().SetLocalPosition(216, 180, 0);
			scene.Add(go);


			//Course title
			go = std::make_shared<GameObject>();
			textureRenderer = go->AddComponent<CTextureRenderer>();
			auto textTexture = go->AddComponent<CTextTexture>();

			textTexture->SetText("Programming 4 Assignment");
			textTexture->SetFont(ResourceManager::GetInstance().LoadFont("Lingua.otf", 36));
			go->GetTransform().SetLocalPosition(80, 20, 0);
			scene.Add(go);
		}
	}
}