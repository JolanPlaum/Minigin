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
			auto go = scene.CreateObject();
			auto textureRenderer = go->AddComponent<CTextureRenderer>();

			textureRenderer->SetTexture(ResourceManager::GetInstance().LoadTexture("background.tga"));


			//DAE logo
			go = scene.CreateObject();
			textureRenderer = go->AddComponent<CTextureRenderer>();

			textureRenderer->SetTexture(ResourceManager::GetInstance().LoadTexture("logo.tga"));
			go->GetTransform().SetLocalPosition(216, 180);


			//Course title
			go = scene.CreateObject();
			textureRenderer = go->AddComponent<CTextureRenderer>();
			auto textTexture = go->AddComponent<CTextTexture>();

			textTexture->SetText("Programming 4 Assignment");
			textTexture->SetFont(ResourceManager::GetInstance().LoadFont("Lingua.otf", 36));
			go->GetTransform().SetLocalPosition(80, 20);
		}
	}
}