#pragma once
#include "Scene.h"
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

			textureRenderer.lock()->SetTexture(ResourceManager::GetInstance().LoadTexture("background.tga"));
			scene.Add(go);


			//DAE logo
			go = std::make_shared<GameObject>();
			auto transform = go->GetComponent<Transform>();
			textureRenderer = go->AddComponent<CTextureRenderer>();

			textureRenderer.lock()->SetTexture(ResourceManager::GetInstance().LoadTexture("logo.tga"));
			transform.lock()->SetPosition(216, 180, 0);
			scene.Add(go);


			//Course title
			go = std::make_shared<GameObject>();
			transform = go->GetComponent<Transform>();
			textureRenderer = go->AddComponent<CTextureRenderer>();
			auto textTexture = go->AddComponent<CTextTexture>();

			textTexture.lock()->SetText("Programming 4 Assignment");
			textTexture.lock()->SetFont(ResourceManager::GetInstance().LoadFont("Lingua.otf", 36));
			transform.lock()->SetPosition(80, 20, 0);
			scene.Add(go);
		}
	}
}