#include "GameSelector.h"
#include "SceneManager.h"
#include "AssignmentBackground.h"

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
#elif defined(ObserverEventQueues)
#include "ExerciseObserverPrefabs.h"
#include "ResourceManager.h"
#include "SDL_pixels.h"
#include "Subject.h"
#include "Observer.h"
#include "InputManager.h"
#include "ObserverExerciseCommands.h"
#include "ControlsDisplay.h"
#include "AchievementManager.h"
#include "Delegate.h"
#include "Event.h"
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
	auto& scene = SceneManager::GetInstance().CreateScene("Exercise - Commands");
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

	input.AddGamepadCommand(std::make_unique<MoveCommand>(go.get(), glm::vec3{ 0, -1, 0 }, speed),
		InputGamepadBinding{ Gamepad::Button::LeftThumbUp, InputState::Active, ControllerID::One });
	input.AddGamepadCommand(std::make_unique<MoveCommand>(go.get(), glm::vec3{ 0, 1, 0 }, speed),
		InputGamepadBinding{ Gamepad::Button::LeftThumbDown, InputState::Active, ControllerID::One });
	input.AddGamepadCommand(std::make_unique<MoveCommand>(go.get(), glm::vec3{ -1, 0, 0 }, speed),
		InputGamepadBinding{ Gamepad::Button::LeftThumbLeft, InputState::Active, ControllerID::One });
	input.AddGamepadCommand(std::make_unique<MoveCommand>(go.get(), glm::vec3{ 1, 0, 0 }, speed),
		InputGamepadBinding{ Gamepad::Button::LeftThumbRight, InputState::Active, ControllerID::One });
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

#elif defined(ObserverEventQueues)
	auto& scene = SceneManager::GetInstance().CreateScene("Exercise - Observer");
	AssignmentBackground::LoadScene(scene);

	std::shared_ptr<GameObject> go{};
	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 20);
	SDL_Color color{};
	auto& input = InputManager::GetInstance();

	//Player 1
	//========
	ExerciseObserver::CreatePlayer(go);
	auto lives = go->GetComponent<Lives>();
	auto score = go->GetComponent<Score>();
	input.AddGamepadCommand(std::make_unique<ScoreCommand>(go.get(), 50),
		InputGamepadBinding{ Gamepad::Button::ButtonDown, InputState::Pressed, ControllerID::One });
	input.AddGamepadCommand(std::make_unique<DieCommand>(go.get()),
		InputGamepadBinding{ Gamepad::Button::ButtonRight, InputState::Pressed, ControllerID::One });
	input.AddKeyboardCommand(std::make_unique<ScoreCommand>(go.get(), 50),
		InputKeyboardBinding{ Keyboard::Key::SDL_SCANCODE_R, InputState::Pressed });
	input.AddKeyboardCommand(std::make_unique<DieCommand>(go.get()),
		InputKeyboardBinding{ Keyboard::Key::SDL_SCANCODE_E, InputState::Pressed });
	scene.Add(go);

	color = { 255, 255, 0 };
	auto parentUI = std::make_shared<GameObject>();
	parentUI->GetTransform().SetWorldPosition(5, 200, 0);
	scene.Add(parentUI);

	ExerciseObserver::CreateLivesDisplay(go, font, color);
	go->GetComponent<CTextTexture>()->SetText("Lives: " + std::to_string(lives->GetLives()));
	go->GetComponent<LivesDisplay>()->SetLivesComponent(lives);
	go->SetParent(parentUI, false);

	ExerciseObserver::CreateScoreDisplay(go, font, color);
	go->GetTransform().SetLocalPosition(0, 30, 0);
	go->GetComponent<CTextTexture>()->SetText("Score: " + std::to_string(score->GetScore()));
	go->GetComponent<ScoreDisplay>()->SetScoreComponent(score);
	AchievementManager::GetInstance().SetScoreComponent(score);
	go->SetParent(parentUI, false);


	//Player 2
	//========
	ExerciseObserver::CreatePlayer(go);
	lives = go->GetComponent<Lives>();
	score = go->GetComponent<Score>();
	input.AddGamepadCommand(std::make_unique<DieCommand>(go.get()),
		InputGamepadBinding{ Gamepad::Button::ButtonUp, InputState::Pressed, ControllerID::One });
	input.AddGamepadCommand(std::make_unique<ScoreCommand>(go.get(), 25),
		InputGamepadBinding{ Gamepad::Button::ButtonLeft, InputState::Pressed, ControllerID::One });
	scene.Add(go);

	color = { 0, 255, 0 };
	parentUI = std::make_shared<GameObject>();
	parentUI->GetTransform().SetWorldPosition(5, 300, 0);
	scene.Add(parentUI);

	ExerciseObserver::CreateLivesDisplay(go, font, color);
	go->GetComponent<CTextTexture>()->SetText("Lives: " + std::to_string(lives->GetLives()));
	go->GetComponent<LivesDisplay>()->SetLivesComponent(lives);
	go->SetParent(parentUI, false);

	ExerciseObserver::CreateScoreDisplay(go, font, color);
	go->GetTransform().SetLocalPosition(0, 30, 0);
	go->GetComponent<CTextTexture>()->SetText("Score: " + std::to_string(score->GetScore()));
	go->GetComponent<ScoreDisplay>()->SetScoreComponent(score);
	go->SetParent(parentUI, false);


	//Controls Display
	go = std::make_shared<GameObject>();
	go->AddComponent<ControlsDisplay>();
	scene.Add(go);

#endif
}
