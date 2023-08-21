#include "GameSelector.h"
#include "SceneManager.h"
#include "Scene.h"
#include "GameObject.h"
#include "Transform.h"
#define NOMINMAX


#ifdef Demo
#include "Scene.h"
#include "ResourceManager.h"

#include "GameObject.h"
#include "Transform.h"
#include "CTextureRenderer.h"
#include "CTextTexture.h"
#elif defined(SinglePlayer)
#include "LevelTiles.h"
#include "BubblesPrefab.h"
#include <glm/vec2.hpp>
#include <vector>
#include "Renderer.h"
#include "InputManager.h"
#include "EntityCollision.h"
#include "Dragon.h"
#include "KeepSpriteSheetCentered.h"
#include "BubbleTestingCommands.h"
#include "EnemiesPrefab.h"
#include "PlayerPrefabs.h"
#include "Lives.h"
#include "Score.h"
#endif

void dae::LoadGame()
{
	std::cout << "\nControls: {Keyboard} & {Gamepad}\n";
	std::cout << "\n - Player 1: Keyboard and Controller1\n";
	std::cout << "\tLeft: A & DpadLeft/LeftThumbstickLeft\n";
	std::cout << "\tRight: D & DpadRight/LeftThumbstickRight\n";
	std::cout << "\tJump: W & FaceButtonLeft/FaceButtonDown\n";
	std::cout << "\tAttack: LCTRL/SPACE & FaceButtonRight/FaceButtonUp\n";
	std::cout << "\n - Player 2: Keyboard and Controller2\n";
	std::cout << "\tLeft: ArrowLeft & DpadLeft/LeftThumbstickLeft\n";
	std::cout << "\tRight: ArrowRight & DpadRight/LeftThumbstickRight\n";
	std::cout << "\tJump: ArrowUp & FaceButtonLeft/FaceButtonDown\n";
	std::cout << "\tAttack: RCTRL/Num0 & FaceButtonRight/FaceButtonUp\n";

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

#elif defined(SinglePlayer)
	auto& scene = SceneManager::GetInstance().CreateScene("SinglePlayer");

	const glm::vec2 gameSize{ 256, 224 };
	glm::ivec2 screenSize{};
	SDL_GetRendererOutputSize(Renderer::GetInstance().GetSDLRenderer(), &screenSize.x, &screenSize.y);

	// Calculate game to screen scalar and center position
	float baseScale{ trunc(std::min(screenSize.x / gameSize.x, screenSize.y / gameSize.y)) };
	glm::vec2 baseOffset{ (screenSize.x - gameSize.x * baseScale) / 2.f, 0.f };
	GameObject* pBaseParent = scene.CreateObject();
	pBaseParent->GetTransform().SetLocalScale(baseScale);
	pBaseParent->GetTransform().SetLocalPosition(baseOffset);

	// Parent of all the tiles
	{
		GameObject* pWorld = scene.CreateObject();
		pWorld->SetParent(pBaseParent);

		std::vector<glm::vec2> bigTiles{
			// Left Big Wall
			{   0,   0 },
			{   0,  16 },
			{   0,  32 },
			{   0,  48 },
			{   0,  64 },
			{   0,  80 },
			{   0,  96 },
			{   0, 112 },
			{   0, 128 },
			{   0, 144 },
			{   0, 160 },
			{   0, 176 },
			{   0, 192 },

			// Right Big Wall
			{ 240,   0 },
			{ 240,  16 },
			{ 240,  32 },
			{ 240,  48 },
			{ 240,  64 },
			{ 240,  80 },
			{ 240,  96 },
			{ 240, 112 },
			{ 240, 128 },
			{ 240, 144 },
			{ 240, 160 },
			{ 240, 176 },
			{ 240, 192 }
		};
		std::vector<glm::vec2> smallTiles{
			// Bottom Floor
			{  16,   0 },
			{  24,   0 },
			{  32,   0 },
			{  40,   0 },
			{  48,   0 },
			{  56,   0 },
			{  64,   0 },

			{ 104,   0 },
			{ 112,   0 },
			{ 120,   0 },
			{ 128,   0 },
			{ 136,   0 },
			{ 144,   0 },

			{ 184,   0 },
			{ 192,   0 },
			{ 200, 0 },
			{ 208, 0 },
			{ 216,   0 },
			{ 224,   0 },
			{ 232,   0 },

			// Bottom Holes
			{ 72,   0 },
			{ 80,   0 },
			{ 88,   0 },
			{ 96,   0 },

			{ 152,   0 },
			{ 160,   0 },
			{ 168,   0 },
			{ 176,   0 },

			// Platform 1		Platform 2			Platform 3
			{ 16,  40 }, { 16,  80 }, { 16, 120 },
			{ 24,  40 }, { 24,  80 }, { 24, 120 },
			{ 56,  40 }, { 56,  80 }, { 56, 120 },
			{ 64,  40 }, { 64,  80 }, { 64, 120 },
			{ 72,  40 }, { 72,  80 }, { 72, 120 },
			{ 80,  40 }, { 80,  80 }, { 80, 120 },
			{ 88,  40 }, { 88,  80 }, { 88, 120 },
			{ 96,  40 }, { 96,  80 }, { 96, 120 },
			{ 104,  40 }, { 104,  80 }, { 104, 120 },
			{ 112,  40 }, { 112,  80 }, { 112, 120 },
			{ 120,  40 }, { 120,  80 }, { 120, 120 },
			{ 128,  40 }, { 128,  80 }, { 128, 120 },
			{ 136,  40 }, { 136,  80 }, { 136, 120 },
			{ 144,  40 }, { 144,  80 }, { 144, 120 },
			{ 152,  40 }, { 152,  80 }, { 152, 120 },
			{ 160,  40 }, { 160,  80 }, { 160, 120 },
			{ 168,  40 }, { 168,  80 }, { 168, 120 },
			{ 176,  40 }, { 176,  80 }, { 176, 120 },
			{ 184,  40 }, { 184,  80 }, { 184, 120 },
			{ 192,  40 }, { 192,  80 }, { 192, 120 },
			{ 224,  40 }, { 224,  80 }, { 224, 120 },
			{ 232,  40 }, { 232,  80 }, { 232, 120 },
		};
		std::vector<glm::vec2> topTiles{
			// Top Roof
			{  16, 200 },
			{  24, 200 },
			{  32, 200 },
			{  40, 200 },
			{  48, 200 },
			{  56, 200 },
			{  64, 200 },

			{ 104, 200 },
			{ 112, 200 },
			{ 120, 200 },
			{ 128, 200 },
			{ 136, 200 },
			{ 144, 200 },

			{ 184, 200 },
			{ 192, 200 },
			{ 200, 200 },
			{ 208, 200 },
			{ 216, 200 },
			{ 224, 200 },
			{ 232, 200 },

			// Top Holes
			{  72, 200 },
			{  80, 200 },
			{  88, 200 },
			{  96, 200 },

			{ 152, 200 },
			{ 160, 200 },
			{ 168, 200 },
			{ 176, 200 }
		};

		for (const glm::vec2& pos : bigTiles)
		{
			GameObject* pGo = LevelTileBig(scene, 0);
			pGo->SetParent(pWorld);
			pGo->GetTransform().SetLocalPosition(pos);
		}
		for (const glm::vec2& pos : smallTiles)
		{
			GameObject* pGo = LevelTileSmall(scene, 0);
			pGo->SetParent(pWorld);
			pGo->GetTransform().SetLocalPosition(pos);
		}
		for (const glm::vec2& pos : topTiles)
		{
			GameObject* pGo = LevelTileSmall(scene, 0);
			pGo->SetTag("Roof");
			pGo->SetParent(pWorld);
			pGo->GetTransform().SetLocalPosition(pos);
		}
	}

	// Player
	{
		GameObject* pBob = BobPrefab(&scene);
		pBob->GetTransform().SetLocalPosition({ gameSize / 2.f });
		pBob->SetParent(pBaseParent);
		pBob->GetComponent<Dragon>()->TransitionToNewLevel({ 32, 8 });
		pBob->GetComponent<Dragon>()->NewLevelLoaded();

		//Comment Bub for 1 player game
		GameObject* pBub = BubPrefab(&scene);
		pBub->GetTransform().SetLocalPosition({ gameSize / 2.f });
		pBub->SetParent(pBaseParent);
		pBub->GetComponent<Dragon>()->TransitionToNewLevel({ 224, 8 });
		pBub->GetComponent<Dragon>()->NewLevelLoaded();
	}

	GameObject* pEnemies = scene.CreateObject();
	pEnemies->SetParent(pBaseParent);
	// Zen Chan
	{
		std::vector<glm::vec2> zenChans{
			{ 120, 128 },
			{ 120, 144 },
			{ 120, 160 },
		};

		for (const glm::vec2& pos : zenChans)
		{
			GameObject* pGo = ZenChanPrefab(&scene);
			pGo->SetParent(pEnemies);
			pGo->GetTransform().SetLocalPosition(pos);
		}
	}

#endif
}
