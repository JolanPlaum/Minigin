#include "GameSelector.h"
#include "SceneManager.h"

#ifdef Demo
#include "AssignmentBackground.h"
#elif defined(UpdatingGameObjects)
#include "AssignmentBackground.h"
#include "GameObject.h"
#include "CTextTexture.h"
#include "CTextureRenderer.h"
#include "FPS.h"
#include "ResourceManager.h"
#elif defined(SceneGraphDemo)
#include "TestSceneGraph.h"
#elif defined(Scenegraph)
#include "AssignmentBackground.h"
#include "FPS.h"
#include "RotationMovement.h"
#endif

void dae::LoadGame()
{
#ifdef Demo
	auto& scene = SceneManager::GetInstance().CreateScene("Demo");
	AssignmentBackground::LoadScene(scene);
#elif defined(UpdatingGameObjects)
	auto& scene = SceneManager::GetInstance().CreateScene("Exercise - FPS");
	AssignmentBackground::LoadScene(scene);

	auto go = std::make_shared<GameObject>();
	auto text = go->AddComponent<CTextTexture>();
	go->AddComponent<CTextureRenderer>();
	go->AddComponent<FPS>();
	text.lock()->SetFont(ResourceManager::GetInstance().LoadFont("Lingua.otf", 20));
	text.lock()->SetColor(200, 200, 0);
	scene.Add(go);
#elif defined(SceneGraphDemo)
	auto& scene = SceneManager::GetInstance().CreateScene("SceneGraph Demo");
	TestSceneGraph::LoadScene(scene);
#elif defined(Scenegraph)
	auto& scene = SceneManager::GetInstance().CreateScene("Exercise - Scenegraph");
	AssignmentBackground::LoadScene(scene);

	//FPS Object
	auto go = std::make_shared<GameObject>();
	auto text = go->AddComponent<CTextTexture>();
	go->AddComponent<CTextureRenderer>();
	go->AddComponent<FPS>();
	text.lock()->SetFont(ResourceManager::GetInstance().LoadFont("Lingua.otf", 20));
	text.lock()->SetColor(200, 200, 0);
	scene.Add(go);

	//Emtpy root object
	go = std::make_shared<GameObject>();
	go->GetTransform().SetLocalPosition(320, 280, 0);
	scene.Add(go);

	//Parent object
	auto parent = std::make_shared<GameObject>();
	auto textureRenderer = parent->AddComponent<CTextureRenderer>();
	auto rotator = parent->AddComponent<RotationMovement>();
	rotator.lock()->SetRadius(16.f);
	rotator.lock()->SetSpeedDegrees(180.f);
	textureRenderer.lock()->SetTexture(ResourceManager::GetInstance().LoadTexture("Enemy1.png"));
	parent->SetParent(go);

	//Child object
	auto child = std::make_shared<GameObject>();
	textureRenderer = child->AddComponent<CTextureRenderer>();
	rotator = child->AddComponent<RotationMovement>();
	rotator.lock()->SetRadius(16.f);
	rotator.lock()->SetSpeedDegrees(-360.f);
	textureRenderer.lock()->SetTexture(ResourceManager::GetInstance().LoadTexture("Enemy2.png"));
	child->SetParent(parent, false);
#endif
}
