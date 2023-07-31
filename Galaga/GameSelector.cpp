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
#include "Delegate.h"
#include "Event.h"
#elif defined(Collision)
#include "InputManager.h"
#include "ResourceManager.h"
#include "ServiceLocator.h"
#include "Event.h"
#include "ExerciseObserverPrefabs.h"
#include "ObserverExerciseCommands.h"
#include "MoveCommand.h"
#include "BoxCollider2D.h"
#include "GalagaPlayer.h"
#elif defined(FinalGame)
#include "ServiceLocator.h"
#include "InputManager.h"
#endif

void dae::LoadGame()
{
#ifdef Demo
	auto& scene = SceneManager::GetInstance().CreateScene("Demo");
	AssignmentBackground::LoadScene(scene);
#elif defined(UpdatingGameObjects)
	auto& scene = SceneManager::GetInstance().CreateScene("Exercise - FPS");
	AssignmentBackground::LoadScene(scene);

	auto go = scene.CreateObject();
	auto text = go->AddComponent<CTextTexture>();
	go->AddComponent<CTextureRenderer>();
	go->AddComponent<FPS>();
	text->SetFont(ResourceManager::GetInstance().LoadFont("Lingua.otf", 20));
	text->SetColor(200, 200, 0);
#elif defined(SceneGraphDemo)
	auto& scene = SceneManager::GetInstance().CreateScene("SceneGraph Demo");
	TestSceneGraph::LoadScene(scene);
#elif defined(Scenegraph)
	auto& scene = SceneManager::GetInstance().CreateScene("Exercise - Scenegraph");
	AssignmentBackground::LoadScene(scene);

	//FPS Object
	auto go = scene.CreateObject();
	auto text = go->AddComponent<CTextTexture>();
	go->AddComponent<CTextureRenderer>();
	go->AddComponent<FPS>();
	text->SetFont(ResourceManager::GetInstance().LoadFont("Lingua.otf", 20));
	text->SetColor(200, 200, 0);

	//Emtpy root object
	go = scene.CreateObject();
	go->GetTransform().SetLocalPosition(320, 280, 0);

	//Parent object
	auto parent = scene.CreateObject();
	auto textureRenderer = parent->AddComponent<CTextureRenderer>();
	auto rotator = parent->AddComponent<RotationMovement>();
	rotator->SetRadius(16.f);
	rotator->SetSpeedDegrees(180.f);
	textureRenderer->SetTexture(ResourceManager::GetInstance().LoadTexture("Enemy1.png"));
	parent->SetParent(go);

	//Child object
	auto child = scene.CreateObject();
	textureRenderer = child->AddComponent<CTextureRenderer>();
	rotator = child->AddComponent<RotationMovement>();
	rotator->SetRadius(16.f);
	rotator->SetSpeedDegrees(-360.f);
	textureRenderer->SetTexture(ResourceManager::GetInstance().LoadTexture("Enemy2.png"));
	child->SetParent(parent, false);
#elif defined(DearImGui)
	auto& scene = SceneManager::GetInstance().CreateScene("DearImGui - Trash the cache");
	AssignmentBackground::LoadScene(scene);

	auto go = scene.CreateObject();
	go->AddComponent<TrashTheCache>();
#elif defined(Commands)
	auto& scene = SceneManager::GetInstance().CreateScene("Exercise - Commands");
	AssignmentBackground::LoadScene(scene);

	auto& input = InputManager::GetInstance();

	//Controller input object
	auto go = scene.CreateObject();
	auto textureRenderer = go->AddComponent<CTextureRenderer>();
	textureRenderer->SetTexture(ResourceManager::GetInstance().LoadTexture("Enemy1.png"));
	float speed = 100.f;
	input.AddGamepadCommand(std::make_unique<MoveCommand>(go, glm::vec3{ 0, -1, 0 }, speed),
		InputGamepadBinding{ Gamepad::Button::DpadUp, InputState::Active, ControllerID::One });
	input.AddGamepadCommand(std::make_unique<MoveCommand>(go, glm::vec3{ 0, 1, 0 }, speed),
		InputGamepadBinding{ Gamepad::Button::DpadDown, InputState::Active, ControllerID::One });
	input.AddGamepadCommand(std::make_unique<MoveCommand>(go, glm::vec3{ -1, 0, 0 }, speed),
		InputGamepadBinding{ Gamepad::Button::DpadLeft, InputState::Active, ControllerID::One });
	input.AddGamepadCommand(std::make_unique<MoveCommand>(go, glm::vec3{ 1, 0, 0 }, speed),
		InputGamepadBinding{ Gamepad::Button::DpadRight, InputState::Active, ControllerID::One });

	input.AddGamepadCommand(std::make_unique<MoveCommand>(go, glm::vec3{ 0, -1, 0 }, speed),
		InputGamepadBinding{ Gamepad::Button::LeftThumbUp, InputState::Active, ControllerID::One });
	input.AddGamepadCommand(std::make_unique<MoveCommand>(go, glm::vec3{ 0, 1, 0 }, speed),
		InputGamepadBinding{ Gamepad::Button::LeftThumbDown, InputState::Active, ControllerID::One });
	input.AddGamepadCommand(std::make_unique<MoveCommand>(go, glm::vec3{ -1, 0, 0 }, speed),
		InputGamepadBinding{ Gamepad::Button::LeftThumbLeft, InputState::Active, ControllerID::One });
	input.AddGamepadCommand(std::make_unique<MoveCommand>(go, glm::vec3{ 1, 0, 0 }, speed),
		InputGamepadBinding{ Gamepad::Button::LeftThumbRight, InputState::Active, ControllerID::One });

	//Keyboard input object
	go = scene.CreateObject();
	textureRenderer = go->AddComponent<CTextureRenderer>();
	textureRenderer->SetTexture(ResourceManager::GetInstance().LoadTexture("Enemy2.png"));
	speed *= 2;
	input.AddKeyboardCommand(std::make_unique<MoveCommand>(go, glm::vec3{ 0, -1, 0 }, speed),
		InputKeyboardBinding{ Keyboard::Key::SDL_SCANCODE_W, InputState::Active });
	input.AddKeyboardCommand(std::make_unique<MoveCommand>(go, glm::vec3{ 0, 1, 0 }, speed),
		InputKeyboardBinding{ Keyboard::Key::SDL_SCANCODE_S, InputState::Active });
	input.AddKeyboardCommand(std::make_unique<MoveCommand>(go, glm::vec3{ -1, 0, 0 }, speed),
		InputKeyboardBinding{ Keyboard::Key::SDL_SCANCODE_A, InputState::Active });
	input.AddKeyboardCommand(std::make_unique<MoveCommand>(go, glm::vec3{ 1, 0, 0 }, speed),
		InputKeyboardBinding{ Keyboard::Key::SDL_SCANCODE_D, InputState::Active });

#elif defined(ObserverEventQueues)
	auto& scene = SceneManager::GetInstance().CreateScene("Exercise - Observer");
	AssignmentBackground::LoadScene(scene);

	std::shared_ptr<GameObject> go{};
	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 20);
	SDL_Color color{};
	auto& input = InputManager::GetInstance();

	//Player 1
	//========
	go = scene.CreateObject();
	ExerciseObserver::CreatePlayer(go);
	auto lives = go->GetComponent<Lives>();
	auto score = go->GetComponent<Score>();
	input.AddGamepadCommand(std::make_unique<ScoreCommand>(go, 50),
		InputGamepadBinding{ Gamepad::Button::ButtonDown, InputState::Pressed, ControllerID::One });
	input.AddGamepadCommand(std::make_unique<DieCommand>(go),
		InputGamepadBinding{ Gamepad::Button::ButtonRight, InputState::Pressed, ControllerID::One });
	input.AddKeyboardCommand(std::make_unique<ScoreCommand>(go, 50),
		InputKeyboardBinding{ Keyboard::Key::SDL_SCANCODE_R, InputState::Pressed });
	input.AddKeyboardCommand(std::make_unique<DieCommand>(go),
		InputKeyboardBinding{ Keyboard::Key::SDL_SCANCODE_E, InputState::Pressed });

	color = { 255, 255, 0 };
	auto parentUI = scene.CreateObject();
	parentUI->GetTransform().SetWorldPosition(5, 200, 0);

	go = scene.CreateObject();
	ExerciseObserver::CreateLivesDisplay(go, font, color);
	go->GetComponent<CTextTexture>()->SetText("Lives: " + std::to_string(lives->GetLives()));
	go->GetComponent<LivesDisplay>()->SetLivesComponent(lives);
	go->SetParent(parentUI, false);

	go = scene.CreateObject();
	ExerciseObserver::CreateScoreDisplay(go, font, color);
	go->GetTransform().SetLocalPosition(0, 30, 0);
	go->GetComponent<CTextTexture>()->SetText("Score: " + std::to_string(score->GetScore()));
	go->GetComponent<ScoreDisplay>()->SetScoreComponent(score);
	go->SetParent(parentUI, false);


	//Player 2
	//========
	go = scene.CreateObject();
	ExerciseObserver::CreatePlayer(go);
	lives = go->GetComponent<Lives>();
	score = go->GetComponent<Score>();
	input.AddGamepadCommand(std::make_unique<DieCommand>(go),
		InputGamepadBinding{ Gamepad::Button::ButtonUp, InputState::Pressed, ControllerID::One });
	input.AddGamepadCommand(std::make_unique<ScoreCommand>(go, 25),
		InputGamepadBinding{ Gamepad::Button::ButtonLeft, InputState::Pressed, ControllerID::One });

	color = { 0, 255, 0 };
	parentUI = scene.CreateObject();
	parentUI->GetTransform().SetWorldPosition(5, 300, 0);

	go = scene.CreateObject();
	ExerciseObserver::CreateLivesDisplay(go, font, color);
	go->GetComponent<CTextTexture>()->SetText("Lives: " + std::to_string(lives->GetLives()));
	go->GetComponent<LivesDisplay>()->SetLivesComponent(lives);
	go->SetParent(parentUI, false);

	go = scene.CreateObject();
	ExerciseObserver::CreateScoreDisplay(go, font, color);
	go->GetTransform().SetLocalPosition(0, 30, 0);
	go->GetComponent<CTextTexture>()->SetText("Score: " + std::to_string(score->GetScore()));
	go->GetComponent<ScoreDisplay>()->SetScoreComponent(score);
	go->SetParent(parentUI, false);


	//Controls Display
	go = scene.CreateObject();
	go->AddComponent<ControlsDisplay>();

#elif defined(Collision)
	auto& scene = SceneManager::GetInstance().CreateScene("Collision");
	AssignmentBackground::LoadScene(scene);

	GameObject* go{};
	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 20);
	SDL_Color color{};
	auto& input = InputManager::GetInstance();


	//Player 1
	//========
	go = scene.CreateObject();
	go->SetTag("Friendly");
	go->GetTransform().SetWorldPosition(200, 100, 0);
	auto lives = go->AddComponent<Lives>();
	auto score = go->AddComponent<Score>();
	auto textureRenderer = go->AddComponent<CTextureRenderer>();
	auto collider = go->AddComponent<BoxCollider2D>();
	go->AddComponent<GalagaPlayer>();

	textureRenderer->SetTexture(ResourceManager::GetInstance().LoadTexture("Enemy1.png"));
	collider->SetSize(textureRenderer->GetSize());
	float speed = 100.f;
	input.AddGamepadCommand(std::make_unique<MoveCommand>(go, glm::vec3{ 0, -1, 0 }, speed),
		InputGamepadBinding{ Gamepad::Button::DpadUp, InputState::Active, ControllerID::One });
	input.AddGamepadCommand(std::make_unique<MoveCommand>(go, glm::vec3{ 0, 1, 0 }, speed),
		InputGamepadBinding{ Gamepad::Button::DpadDown, InputState::Active, ControllerID::One });
	input.AddGamepadCommand(std::make_unique<MoveCommand>(go, glm::vec3{ -1, 0, 0 }, speed),
		InputGamepadBinding{ Gamepad::Button::DpadLeft, InputState::Active, ControllerID::One });
	input.AddGamepadCommand(std::make_unique<MoveCommand>(go, glm::vec3{ 1, 0, 0 }, speed),
		InputGamepadBinding{ Gamepad::Button::DpadRight, InputState::Active, ControllerID::One });

	input.AddGamepadCommand(std::make_unique<MoveCommand>(go, glm::vec3{ 0, -1, 0 }, speed),
		InputGamepadBinding{ Gamepad::Button::LeftThumbUp, InputState::Active, ControllerID::One });
	input.AddGamepadCommand(std::make_unique<MoveCommand>(go, glm::vec3{ 0, 1, 0 }, speed),
		InputGamepadBinding{ Gamepad::Button::LeftThumbDown, InputState::Active, ControllerID::One });
	input.AddGamepadCommand(std::make_unique<MoveCommand>(go, glm::vec3{ -1, 0, 0 }, speed),
		InputGamepadBinding{ Gamepad::Button::LeftThumbLeft, InputState::Active, ControllerID::One });
	input.AddGamepadCommand(std::make_unique<MoveCommand>(go, glm::vec3{ 1, 0, 0 }, speed),
		InputGamepadBinding{ Gamepad::Button::LeftThumbRight, InputState::Active, ControllerID::One });

	color = { 255, 255, 0 };
	auto parentUI = scene.CreateObject();
	parentUI->GetTransform().SetWorldPosition(5, 200, 0);

	go = scene.CreateObject();
	ExerciseObserver::CreateLivesDisplay(go, font, color);
	go->GetComponent<CTextTexture>()->SetText("Lives: " + std::to_string(lives->GetLives()));
	go->GetComponent<LivesDisplay>()->SetLivesComponent(lives);
	go->SetParent(parentUI, false);

	go = scene.CreateObject();
	ExerciseObserver::CreateScoreDisplay(go, font, color);
	go->GetTransform().SetLocalPosition(0, 30, 0);
	go->GetComponent<CTextTexture>()->SetText("Score: " + std::to_string(score->GetScore()));
	go->GetComponent<ScoreDisplay>()->SetScoreComponent(score);
	go->SetParent(parentUI, false);


	//Player 2
	//========
	go = scene.CreateObject();
	go->SetTag("Enemy");
	collider = go->AddComponent<BoxCollider2D>();
	textureRenderer = go->AddComponent<CTextureRenderer>();

	textureRenderer->SetTexture(ResourceManager::GetInstance().LoadTexture("Enemy2.png"));
	collider->SetSize(textureRenderer->GetSize());
	speed *= 2;
	input.AddKeyboardCommand(std::make_unique<MoveCommand>(go, glm::vec3{ 0, -1, 0 }, speed),
		InputKeyboardBinding{ Keyboard::Key::SDL_SCANCODE_W, InputState::Active });
	input.AddKeyboardCommand(std::make_unique<MoveCommand>(go, glm::vec3{ 0, 1, 0 }, speed),
		InputKeyboardBinding{ Keyboard::Key::SDL_SCANCODE_S, InputState::Active });
	input.AddKeyboardCommand(std::make_unique<MoveCommand>(go, glm::vec3{ -1, 0, 0 }, speed),
		InputKeyboardBinding{ Keyboard::Key::SDL_SCANCODE_A, InputState::Active });
	input.AddKeyboardCommand(std::make_unique<MoveCommand>(go, glm::vec3{ 1, 0, 0 }, speed),
		InputKeyboardBinding{ Keyboard::Key::SDL_SCANCODE_D, InputState::Active });
	
#elif defined(FinalGame)
	auto& scene = SceneManager::GetInstance().CreateScene("FinalGame");
	AssignmentBackground::LoadScene(scene);

	//auto& input = InputManager::GetInstance();
	
	// Load all the sounds
	Locator::GetSoundSystem().Load("Audio/BossDeath.mp3", 0);
	Locator::GetSoundSystem().Load("Audio/CapturedShip.mp3", 1);
	Locator::GetSoundSystem().Load("Audio/EnemyDies.mp3", 2);
	Locator::GetSoundSystem().Load("Audio/PlayerDies.mp3", 3);
	Locator::GetSoundSystem().Load("Audio/PlayerShoot.mp3", 4);
	Locator::GetSoundSystem().Load("Audio/Start.mp3", 5);
	Locator::GetSoundSystem().Load("Audio/TractorBeam.mp3", 6);

#endif
}
