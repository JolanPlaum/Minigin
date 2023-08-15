#include "GameSelector.h"
#include "SceneManager.h"
#include "Scene.h"
#include "ResourceManager.h"
#include "GameObject.h"
#include "Transform.h"

#ifdef Demo
#include "Scene.h"
#include "ResourceManager.h"

#include "GameObject.h"
#include "Transform.h"
#include "CTextureRenderer.h"
#include "CTextTexture.h"
#elif defined(SinglePlayer)
#include "CSpriteRenderer.h"
#include "Sprite2D.h"
#include "Texture2D.h"
#include "SpriteTestingCommands.h"
#include "InputManager.h"
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

#elif defined(SinglePlayer)
	auto& scene = SceneManager::GetInstance().CreateScene("SinglePlayer");
	auto& input = InputManager::GetInstance();

	auto parent = scene.CreateObject();
	parent->GetTransform().SetLocalPosition(200, 150);
	parent->GetTransform().SetLocalScale(3);

	{
		auto go = scene.CreateObject();
		go->SetParent(parent);
		auto spriteTexture = std::make_shared<Sprite2D>(ResourceManager::GetInstance().LoadTexture("BubbleBobble/Sprites/LevelTilesBig.png"), 10, 1);
		auto sprite = go->AddComponent<CSpriteRenderer>();
		sprite->SetSprite(spriteTexture);
		sprite->SetSettings(SpriteRenderSettings::IterateNone);
		go->GetTransform().SetLocalPosition(-sprite->GetSize().x / 2.f, 0.f);

		input.AddKeyboardCommand(std::make_unique<SetSpriteIdxCommand>(go, true, 1), InputKeyboardBinding{ Keyboard::Key::SDL_SCANCODE_Q, InputState::Pressed });
		input.AddKeyboardCommand(std::make_unique<SetSpriteIdxCommand>(go, true, 7), InputKeyboardBinding{ Keyboard::Key::SDL_SCANCODE_W, InputState::Pressed });
		input.AddKeyboardCommand(std::make_unique<SetSpriteIdxCommand>(go, false, 1), InputKeyboardBinding{ Keyboard::Key::SDL_SCANCODE_A, InputState::Pressed });
		input.AddKeyboardCommand(std::make_unique<SetSpriteIdxCommand>(go, false, 7), InputKeyboardBinding{ Keyboard::Key::SDL_SCANCODE_S, InputState::Pressed });
	}

	{
		auto go = scene.CreateObject();
		go->SetParent(parent);
		auto spriteTexture = std::make_shared<Sprite2D>(ResourceManager::GetInstance().LoadTexture("BubbleBobble/Sprites/Items.png"), 13, 8);
		auto sprite = go->AddComponent<CSpriteRenderer>();
		sprite->SetSprite(spriteTexture, 10.f / 60);
		go->GetTransform().SetLocalPosition(-sprite->GetSize().x / 2.f, 0.f);

		input.AddKeyboardCommand(std::make_unique<PauseSpriteCommand>(go, true), InputKeyboardBinding{ Keyboard::Key::SDL_SCANCODE_P, InputState::Pressed });
		input.AddKeyboardCommand(std::make_unique<PauseSpriteCommand>(go, 1.f), InputKeyboardBinding{ Keyboard::Key::SDL_SCANCODE_1, InputState::Pressed });
		input.AddKeyboardCommand(std::make_unique<PauseSpriteCommand>(go, 2.f), InputKeyboardBinding{ Keyboard::Key::SDL_SCANCODE_2, InputState::Pressed });
		input.AddKeyboardCommand(std::make_unique<PauseSpriteCommand>(go, 5.f), InputKeyboardBinding{ Keyboard::Key::SDL_SCANCODE_3, InputState::Pressed });
		input.AddKeyboardCommand(std::make_unique<PauseSpriteCommand>(go, 10.f), InputKeyboardBinding{ Keyboard::Key::SDL_SCANCODE_4, InputState::Pressed });
	}


	//go->GetTransform().setwo

#endif
}
