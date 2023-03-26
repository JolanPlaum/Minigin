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
#elif defined(DearImGui)
#include "AssignmentBackground.h"
#include "TrashTheCache.h"
#elif defined(Commands)
#include "AssignmentBackground.h"
#include "GameObject.h"
#include "CTextTexture.h"
#include "CTextureRenderer.h"
#include "InputManager.h"
#include "MoveCommand.h"
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
	text->SetFont(ResourceManager::GetInstance().LoadFont("Lingua.otf", 20));
	text->SetColor(200, 200, 0);
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
	text->SetFont(ResourceManager::GetInstance().LoadFont("Lingua.otf", 20));
	text->SetColor(200, 200, 0);
	scene.Add(go);

	//Emtpy root object
	go = std::make_shared<GameObject>();
	go->GetTransform().SetLocalPosition(320, 280, 0);
	scene.Add(go);

	//Parent object
	auto parent = std::make_shared<GameObject>();
	auto textureRenderer = parent->AddComponent<CTextureRenderer>();
	auto rotator = parent->AddComponent<RotationMovement>();
	rotator->SetRadius(16.f);
	rotator->SetSpeedDegrees(180.f);
	textureRenderer->SetTexture(ResourceManager::GetInstance().LoadTexture("Enemy1.png"));
	parent->SetParent(go);

	//Child object
	auto child = std::make_shared<GameObject>();
	textureRenderer = child->AddComponent<CTextureRenderer>();
	rotator = child->AddComponent<RotationMovement>();
	rotator->SetRadius(16.f);
	rotator->SetSpeedDegrees(-360.f);
	textureRenderer->SetTexture(ResourceManager::GetInstance().LoadTexture("Enemy2.png"));
	child->SetParent(parent, false);
#elif defined(DearImGui)
	auto& scene = SceneManager::GetInstance().CreateScene("DearImGui - Trash the cache");
	AssignmentBackground::LoadScene(scene);

	auto go = std::make_shared<GameObject>();
	go->AddComponent<TrashTheCache>();
	scene.Add(go);
#elif defined(Commands)
	auto& scene = SceneManager::GetInstance().CreateScene("Exercise - Scenegraph");
	AssignmentBackground::LoadScene(scene);

	auto& input = InputManager::GetInstance();

	//Controller input object
	auto go = std::make_shared<GameObject>();
	auto textureRenderer = go->AddComponent<CTextureRenderer>();
	textureRenderer->SetTexture(ResourceManager::GetInstance().LoadTexture("Enemy1.png"));
	float speed = 100.f;
	input.AddGamepadCommand(std::make_unique<MoveCommand>(go.get(), glm::vec3{ 0, -1, 0 }, speed),
		InputGamepadBinding{ Gamepad::Button::DpadUp, InputState::Active, ControllerID::One });
	input.AddGamepadCommand(std::make_unique<MoveCommand>(go.get(), glm::vec3{ 0, 1, 0 }, speed),
		InputGamepadBinding{ Gamepad::Button::DpadDown, InputState::Active, ControllerID::One });
	input.AddGamepadCommand(std::make_unique<MoveCommand>(go.get(), glm::vec3{ -1, 0, 0 }, speed),
		InputGamepadBinding{ Gamepad::Button::DpadLeft, InputState::Active, ControllerID::One });
	input.AddGamepadCommand(std::make_unique<MoveCommand>(go.get(), glm::vec3{ 1, 0, 0 }, speed),
		InputGamepadBinding{ Gamepad::Button::DpadRight, InputState::Active, ControllerID::One });
	scene.Add(go);

	//Keyboard input object
	go = std::make_shared<GameObject>();
	textureRenderer = go->AddComponent<CTextureRenderer>();
	textureRenderer->SetTexture(ResourceManager::GetInstance().LoadTexture("Enemy2.png"));
	speed *= 2;
	input.AddKeyboardCommand(std::make_unique<MoveCommand>(go.get(), glm::vec3{ 0, -1, 0 }, speed),
		InputKeyboardBinding{ Keyboard::Key::SDL_SCANCODE_W, InputState::Active });
	input.AddKeyboardCommand(std::make_unique<MoveCommand>(go.get(), glm::vec3{ 0, 1, 0 }, speed),
		InputKeyboardBinding{ Keyboard::Key::SDL_SCANCODE_S, InputState::Active });
	input.AddKeyboardCommand(std::make_unique<MoveCommand>(go.get(), glm::vec3{ -1, 0, 0 }, speed),
		InputKeyboardBinding{ Keyboard::Key::SDL_SCANCODE_A, InputState::Active });
	input.AddKeyboardCommand(std::make_unique<MoveCommand>(go.get(), glm::vec3{ 1, 0, 0 }, speed),
		InputKeyboardBinding{ Keyboard::Key::SDL_SCANCODE_D, InputState::Active });
	scene.Add(go);
#endif
}
