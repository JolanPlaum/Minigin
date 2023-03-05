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
#endif
}
