#include "GameSelector.h"
#include "SceneManager.h"

#ifdef Demo
#include "AssignmentBackground.h"
#endif

void dae::LoadGame()
{
#ifdef Demo
	auto& scene = SceneManager::GetInstance().CreateScene("Demo");
	AssignmentBackground::LoadScene(scene);
#endif
}
