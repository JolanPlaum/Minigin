#pragma once
#include "Scene.h"
#include "Transform.h"
#include "CTexture.h"
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
			auto texture = go->AddComponent<CTexture>();
			auto textureRenderer = go->AddComponent<CTextureRenderer>();

			texture.lock()->SetTexture("background.tga");
			scene.Add(go);


			//DAE logo
			go = std::make_shared<GameObject>();
			auto transform = go->GetComponent<Transform>();
			texture = go->AddComponent<CTexture>();
			textureRenderer = go->AddComponent<CTextureRenderer>();

			texture.lock()->SetTexture("logo.tga");
			transform.lock()->SetPosition(216, 180, 0);
			scene.Add(go);


			//Course title
			go = std::make_shared<GameObject>();
			transform = go->GetComponent<Transform>();
			auto textTexture = go->AddComponent<CTextTexture>();
			textureRenderer = go->AddComponent<CTextureRenderer>();

			textTexture.lock()->SetText("Programming 4 Assignment");
			textTexture.lock()->SetFont(ResourceManager::GetInstance().LoadFont("Lingua.otf", 36));
			transform.lock()->SetPosition(80, 20, 0);
			scene.Add(go);
		}
	}
}