#include "GameSelector.h"
#include "SceneManager.h"

#ifdef Demo
#include "Scene.h"
#include "ResourceManager.h"

#include "GameObject.h"
#include "Transform.h"
#include "CTextureRenderer.h"
#include "CTextTexture.h"
#endif

void dae::LoadGame()
{
#ifdef Demo
	auto& scene = SceneManager::GetInstance().CreateScene("Demo");

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
#endif
}
