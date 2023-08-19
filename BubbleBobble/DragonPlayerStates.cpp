//-----------------------------------------------------------------
// Includes
//-----------------------------------------------------------------
#include "DragonPlayerStates.h"
#include <glm/geometric.hpp>
#include "InputManager.h"
#include "ResourceManager.h"
#include "ServiceLocator.h"
#include "TimeManager.h"
#include "GameObject.h"
#include "Transform.h"
#include "Dragon.h"
#include "EntityCollision.h"
#include "CSpriteRenderer.h"

using namespace dae;


//-----------------------------------------------------------------
// DragonPlayerStateIdle Functions
//-----------------------------------------------------------------
void DragonPlayerStateIdle::OnEnter()
{
	// Set sprite
	{
		auto pSprite = ResourceManager::GetInstance().LoadSprite("BubbleBobble/Sprites/Dragon/Idle_Anim.png");
		auto pRenderer = GetGameObject()->GetComponentInChildren<CSpriteRenderer>();
		pRenderer->SetSprite(pSprite, 20.f / 60.f);
	}

	// Get Entity collision
	m_pEntityCollision = GetGameObject()->GetComponent<EntityCollision>();

	// Set commands
	{
		auto& input = InputManager::GetInstance();
		auto pDragon = GetGameObject()->GetComponent<Dragon>();
		float walkSpeed{ 80.f }, jumpSpeed{ 100.f };

		if (pDragon->GetPlayerIdx() == Player::One)
		{
			// Keyboard
			m_KeyboardCommands.push_back(input.AddKeyboardCommand(std::make_unique<MoveCommand>(GetGameObject(), glm::vec2{ -1, 0 }, walkSpeed),
				InputKeyboardBinding{ Keyboard::Key::SDL_SCANCODE_A, InputState::Active }));
			m_KeyboardCommands.push_back(input.AddKeyboardCommand(std::make_unique<MoveCommand>(GetGameObject(), glm::vec2{ 1, 0 }, walkSpeed),
				InputKeyboardBinding{ Keyboard::Key::SDL_SCANCODE_D, InputState::Active }));
			m_KeyboardCommands.push_back(input.AddKeyboardCommand(std::make_unique<MoveCommand>(GetGameObject(), glm::vec2{ 0, 1 }, jumpSpeed),
				InputKeyboardBinding{ Keyboard::Key::SDL_SCANCODE_W, InputState::Pressed }));

			// Gamepad
			m_GamepadCommands.push_back(input.AddGamepadCommand(std::make_unique<MoveCommand>(GetGameObject(), glm::vec2{ -1, 0 }, walkSpeed),
				InputGamepadBinding{ Gamepad::Button::LeftThumbLeft, InputState::Active, ControllerID::One }));
			m_GamepadCommands.push_back(input.AddGamepadCommand(std::make_unique<MoveCommand>(GetGameObject(), glm::vec2{ 1, 0 }, walkSpeed),
				InputGamepadBinding{ Gamepad::Button::LeftThumbRight, InputState::Active, ControllerID::One }));
			m_GamepadCommands.push_back(input.AddGamepadCommand(std::make_unique<MoveCommand>(GetGameObject(), glm::vec2{ -1, 0 }, walkSpeed),
				InputGamepadBinding{ Gamepad::Button::DpadLeft, InputState::Active, ControllerID::One }));
			m_GamepadCommands.push_back(input.AddGamepadCommand(std::make_unique<MoveCommand>(GetGameObject(), glm::vec2{ 1, 0 }, walkSpeed),
				InputGamepadBinding{ Gamepad::Button::DpadRight, InputState::Active, ControllerID::One }));
			m_GamepadCommands.push_back(input.AddGamepadCommand(std::make_unique<MoveCommand>(GetGameObject(), glm::vec2{ 0, 1 }, jumpSpeed),
				InputGamepadBinding{ Gamepad::Button::ButtonDown, InputState::Pressed, ControllerID::One }));
			m_GamepadCommands.push_back(input.AddGamepadCommand(std::make_unique<MoveCommand>(GetGameObject(), glm::vec2{ 0, 1 }, jumpSpeed),
				InputGamepadBinding{ Gamepad::Button::ButtonLeft, InputState::Pressed, ControllerID::One }));
		}
		else if (pDragon->GetPlayerIdx() == Player::Two)
		{
			// Keyboard
			m_KeyboardCommands.push_back(input.AddKeyboardCommand(std::make_unique<MoveCommand>(GetGameObject(), glm::vec2{ -1, 0 }, walkSpeed),
				InputKeyboardBinding{ Keyboard::Key::SDL_SCANCODE_LEFT, InputState::Active }));
			m_KeyboardCommands.push_back(input.AddKeyboardCommand(std::make_unique<MoveCommand>(GetGameObject(), glm::vec2{ 1, 0 }, walkSpeed),
				InputKeyboardBinding{ Keyboard::Key::SDL_SCANCODE_RIGHT, InputState::Active }));
			m_KeyboardCommands.push_back(input.AddKeyboardCommand(std::make_unique<MoveCommand>(GetGameObject(), glm::vec2{ 0, 1 }, jumpSpeed),
				InputKeyboardBinding{ Keyboard::Key::SDL_SCANCODE_UP, InputState::Pressed }));

			// Gamepad
			m_GamepadCommands.push_back(input.AddGamepadCommand(std::make_unique<MoveCommand>(GetGameObject(), glm::vec2{ -1, 0 }, walkSpeed),
				InputGamepadBinding{ Gamepad::Button::LeftThumbLeft, InputState::Active, ControllerID::Two }));
			m_GamepadCommands.push_back(input.AddGamepadCommand(std::make_unique<MoveCommand>(GetGameObject(), glm::vec2{ 1, 0 }, walkSpeed),
				InputGamepadBinding{ Gamepad::Button::LeftThumbRight, InputState::Active, ControllerID::Two }));
			m_GamepadCommands.push_back(input.AddGamepadCommand(std::make_unique<MoveCommand>(GetGameObject(), glm::vec2{ -1, 0 }, walkSpeed),
				InputGamepadBinding{ Gamepad::Button::DpadLeft, InputState::Active, ControllerID::Two }));
			m_GamepadCommands.push_back(input.AddGamepadCommand(std::make_unique<MoveCommand>(GetGameObject(), glm::vec2{ 1, 0 }, walkSpeed),
				InputGamepadBinding{ Gamepad::Button::DpadRight, InputState::Active, ControllerID::Two }));
			m_GamepadCommands.push_back(input.AddGamepadCommand(std::make_unique<MoveCommand>(GetGameObject(), glm::vec2{ 0, 1 }, jumpSpeed),
				InputGamepadBinding{ Gamepad::Button::ButtonDown, InputState::Pressed, ControllerID::Two }));
			m_GamepadCommands.push_back(input.AddGamepadCommand(std::make_unique<MoveCommand>(GetGameObject(), glm::vec2{ 0, 1 }, jumpSpeed),
				InputGamepadBinding{ Gamepad::Button::ButtonLeft, InputState::Pressed, ControllerID::Two }));
		}
	}

	// Set downwards movement
	m_pMoveCommand = std::make_unique<MoveCommand>(GetGameObject(), glm::vec2{ 0, -1 }, 80.f);
}

void DragonPlayerStateIdle::OnExit()
{
	auto& input = InputManager::GetInstance();
	for (auto pCommand : m_KeyboardCommands)
	{
		input.RemoveKeyboardCommand(pCommand);
	}
	for (auto pCommand : m_GamepadCommands)
	{
		input.RemoveGamepadCommand(pCommand);
	}
}

void DragonPlayerStateIdle::Update()
{
	m_pMoveCommand->Execute();
}

std::unique_ptr<State> DragonPlayerStateIdle::Transition()
{
	if (m_pEntityCollision->IsGoingUp()) return std::make_unique<DragonPlayerStateJumping>(GetGameObject());
	if (m_pEntityCollision->IsGoingLeft() || m_pEntityCollision->IsGoingRight())
		return std::make_unique<DragonPlayerStateWalking>(GetGameObject());

	return nullptr;
}


//-----------------------------------------------------------------
// DragonPlayerStateWalking Functions
//-----------------------------------------------------------------
void DragonPlayerStateWalking::OnEnter()
{
	// Set sprite
	{
		auto pSprite = ResourceManager::GetInstance().LoadSprite("BubbleBobble/Sprites/Dragon/Walk_Anim.png");
		auto pRenderer = GetGameObject()->GetComponentInChildren<CSpriteRenderer>();
		pRenderer->SetSprite(pSprite, 5.f / 60.f);
	}

	// Get Entity collision
	m_pEntityCollision = GetGameObject()->GetComponent<EntityCollision>();

	// Set commands
	{
		auto& input = InputManager::GetInstance();
		auto pDragon = GetGameObject()->GetComponent<Dragon>();
		float walkSpeed{ 80.f }, jumpSpeed{ 100.f };

		if (pDragon->GetPlayerIdx() == Player::One)
		{
			// Keyboard
			m_KeyboardCommands.push_back(input.AddKeyboardCommand(std::make_unique<MoveCommand>(GetGameObject(), glm::vec2{ -1, 0 }, walkSpeed),
				InputKeyboardBinding{ Keyboard::Key::SDL_SCANCODE_A, InputState::Active }));
			m_KeyboardCommands.push_back(input.AddKeyboardCommand(std::make_unique<MoveCommand>(GetGameObject(), glm::vec2{ 1, 0 }, walkSpeed),
				InputKeyboardBinding{ Keyboard::Key::SDL_SCANCODE_D, InputState::Active }));
			m_KeyboardCommands.push_back(input.AddKeyboardCommand(std::make_unique<MoveCommand>(GetGameObject(), glm::vec2{ 0, 1 }, jumpSpeed),
				InputKeyboardBinding{ Keyboard::Key::SDL_SCANCODE_W, InputState::Pressed }));

			// Gamepad
			m_GamepadCommands.push_back(input.AddGamepadCommand(std::make_unique<MoveCommand>(GetGameObject(), glm::vec2{ -1, 0 }, walkSpeed),
				InputGamepadBinding{ Gamepad::Button::LeftThumbLeft, InputState::Active, ControllerID::One }));
			m_GamepadCommands.push_back(input.AddGamepadCommand(std::make_unique<MoveCommand>(GetGameObject(), glm::vec2{ 1, 0 }, walkSpeed),
				InputGamepadBinding{ Gamepad::Button::LeftThumbRight, InputState::Active, ControllerID::One }));
			m_GamepadCommands.push_back(input.AddGamepadCommand(std::make_unique<MoveCommand>(GetGameObject(), glm::vec2{ -1, 0 }, walkSpeed),
				InputGamepadBinding{ Gamepad::Button::DpadLeft, InputState::Active, ControllerID::One }));
			m_GamepadCommands.push_back(input.AddGamepadCommand(std::make_unique<MoveCommand>(GetGameObject(), glm::vec2{ 1, 0 }, walkSpeed),
				InputGamepadBinding{ Gamepad::Button::DpadRight, InputState::Active, ControllerID::One }));
			m_GamepadCommands.push_back(input.AddGamepadCommand(std::make_unique<MoveCommand>(GetGameObject(), glm::vec2{ 0, 1 }, jumpSpeed),
				InputGamepadBinding{ Gamepad::Button::ButtonDown, InputState::Pressed, ControllerID::One }));
			m_GamepadCommands.push_back(input.AddGamepadCommand(std::make_unique<MoveCommand>(GetGameObject(), glm::vec2{ 0, 1 }, jumpSpeed),
				InputGamepadBinding{ Gamepad::Button::ButtonLeft, InputState::Pressed, ControllerID::One }));
		}
		else if (pDragon->GetPlayerIdx() == Player::Two)
		{
			// Keyboard
			m_KeyboardCommands.push_back(input.AddKeyboardCommand(std::make_unique<MoveCommand>(GetGameObject(), glm::vec2{ -1, 0 }, walkSpeed),
				InputKeyboardBinding{ Keyboard::Key::SDL_SCANCODE_LEFT, InputState::Active }));
			m_KeyboardCommands.push_back(input.AddKeyboardCommand(std::make_unique<MoveCommand>(GetGameObject(), glm::vec2{ 1, 0 }, walkSpeed),
				InputKeyboardBinding{ Keyboard::Key::SDL_SCANCODE_RIGHT, InputState::Active }));
			m_KeyboardCommands.push_back(input.AddKeyboardCommand(std::make_unique<MoveCommand>(GetGameObject(), glm::vec2{ 0, 1 }, jumpSpeed),
				InputKeyboardBinding{ Keyboard::Key::SDL_SCANCODE_UP, InputState::Pressed }));

			// Gamepad
			m_GamepadCommands.push_back(input.AddGamepadCommand(std::make_unique<MoveCommand>(GetGameObject(), glm::vec2{ -1, 0 }, walkSpeed),
				InputGamepadBinding{ Gamepad::Button::LeftThumbLeft, InputState::Active, ControllerID::Two }));
			m_GamepadCommands.push_back(input.AddGamepadCommand(std::make_unique<MoveCommand>(GetGameObject(), glm::vec2{ 1, 0 }, walkSpeed),
				InputGamepadBinding{ Gamepad::Button::LeftThumbRight, InputState::Active, ControllerID::Two }));
			m_GamepadCommands.push_back(input.AddGamepadCommand(std::make_unique<MoveCommand>(GetGameObject(), glm::vec2{ -1, 0 }, walkSpeed),
				InputGamepadBinding{ Gamepad::Button::DpadLeft, InputState::Active, ControllerID::Two }));
			m_GamepadCommands.push_back(input.AddGamepadCommand(std::make_unique<MoveCommand>(GetGameObject(), glm::vec2{ 1, 0 }, walkSpeed),
				InputGamepadBinding{ Gamepad::Button::DpadRight, InputState::Active, ControllerID::Two }));
			m_GamepadCommands.push_back(input.AddGamepadCommand(std::make_unique<MoveCommand>(GetGameObject(), glm::vec2{ 0, 1 }, jumpSpeed),
				InputGamepadBinding{ Gamepad::Button::ButtonDown, InputState::Pressed, ControllerID::Two }));
			m_GamepadCommands.push_back(input.AddGamepadCommand(std::make_unique<MoveCommand>(GetGameObject(), glm::vec2{ 0, 1 }, jumpSpeed),
				InputGamepadBinding{ Gamepad::Button::ButtonLeft, InputState::Pressed, ControllerID::Two }));
		}
	}

	// Set downwards movement
	m_pMoveCommand = std::make_unique<MoveCommand>(GetGameObject(), glm::vec2{ 0, -1 }, 80.f);
}

void DragonPlayerStateWalking::OnExit()
{
	auto& input = InputManager::GetInstance();
	for (auto pCommand : m_KeyboardCommands)
	{
		input.RemoveKeyboardCommand(pCommand);
	}
	for (auto pCommand : m_GamepadCommands)
	{
		input.RemoveGamepadCommand(pCommand);
	}
}

void DragonPlayerStateWalking::Update()
{
	m_pMoveCommand->Execute();
}

std::unique_ptr<State> DragonPlayerStateWalking::Transition()
{
	if (m_pEntityCollision->IsGoingUp()) return std::make_unique<DragonPlayerStateJumping>(GetGameObject());
	if (m_pEntityCollision->IsGoingDown()) return std::make_unique<DragonPlayerStateFalling>(GetGameObject());
	if (m_pEntityCollision->IsGoingLeft() || m_pEntityCollision->IsGoingRight()) return nullptr;
	return std::make_unique<DragonPlayerStateIdle>(GetGameObject());
}


//-----------------------------------------------------------------
// DragonPlayerStateJumping Functions
//-----------------------------------------------------------------
void DragonPlayerStateJumping::OnEnter()
{
	// Set sprite
	{
		auto pSprite = ResourceManager::GetInstance().LoadSprite("BubbleBobble/Sprites/Dragon/Jump_Anim.png");
		auto pRenderer = GetGameObject()->GetComponentInChildren<CSpriteRenderer>();
		pRenderer->SetSprite(pSprite, 10.f / 60.f);
	}

	// Play sound
	Locator::GetSoundSystem().Play("BubbleBobble/Audio/Jump.wav", 1.f);

	// Get Entity collision
	m_pEntityCollision = GetGameObject()->GetComponent<EntityCollision>();

	// Set commands
	{
		auto& input = InputManager::GetInstance();
		auto pDragon = GetGameObject()->GetComponent<Dragon>();
		float walkSpeed{ 20.f };

		if (pDragon->GetPlayerIdx() == Player::One)
		{
			// Keyboard
			m_KeyboardCommands.push_back(input.AddKeyboardCommand(std::make_unique<MoveCommand>(GetGameObject(), glm::vec2{ -1, 0 }, walkSpeed),
				InputKeyboardBinding{ Keyboard::Key::SDL_SCANCODE_A, InputState::Active }));
			m_KeyboardCommands.push_back(input.AddKeyboardCommand(std::make_unique<MoveCommand>(GetGameObject(), glm::vec2{ 1, 0 }, walkSpeed),
				InputKeyboardBinding{ Keyboard::Key::SDL_SCANCODE_D, InputState::Active }));

			// Gamepad
			m_GamepadCommands.push_back(input.AddGamepadCommand(std::make_unique<MoveCommand>(GetGameObject(), glm::vec2{ -1, 0 }, walkSpeed),
				InputGamepadBinding{ Gamepad::Button::LeftThumbLeft, InputState::Active, ControllerID::One }));
			m_GamepadCommands.push_back(input.AddGamepadCommand(std::make_unique<MoveCommand>(GetGameObject(), glm::vec2{ 1, 0 }, walkSpeed),
				InputGamepadBinding{ Gamepad::Button::LeftThumbRight, InputState::Active, ControllerID::One }));
			m_GamepadCommands.push_back(input.AddGamepadCommand(std::make_unique<MoveCommand>(GetGameObject(), glm::vec2{ -1, 0 }, walkSpeed),
				InputGamepadBinding{ Gamepad::Button::DpadLeft, InputState::Active, ControllerID::One }));
			m_GamepadCommands.push_back(input.AddGamepadCommand(std::make_unique<MoveCommand>(GetGameObject(), glm::vec2{ 1, 0 }, walkSpeed),
				InputGamepadBinding{ Gamepad::Button::DpadRight, InputState::Active, ControllerID::One }));
		}
		else if (pDragon->GetPlayerIdx() == Player::Two)
		{
			// Keyboard
			m_KeyboardCommands.push_back(input.AddKeyboardCommand(std::make_unique<MoveCommand>(GetGameObject(), glm::vec2{ -1, 0 }, walkSpeed),
				InputKeyboardBinding{ Keyboard::Key::SDL_SCANCODE_LEFT, InputState::Active }));
			m_KeyboardCommands.push_back(input.AddKeyboardCommand(std::make_unique<MoveCommand>(GetGameObject(), glm::vec2{ 1, 0 }, walkSpeed),
				InputKeyboardBinding{ Keyboard::Key::SDL_SCANCODE_RIGHT, InputState::Active }));

			// Gamepad
			m_GamepadCommands.push_back(input.AddGamepadCommand(std::make_unique<MoveCommand>(GetGameObject(), glm::vec2{ -1, 0 }, walkSpeed),
				InputGamepadBinding{ Gamepad::Button::LeftThumbLeft, InputState::Active, ControllerID::Two }));
			m_GamepadCommands.push_back(input.AddGamepadCommand(std::make_unique<MoveCommand>(GetGameObject(), glm::vec2{ 1, 0 }, walkSpeed),
				InputGamepadBinding{ Gamepad::Button::LeftThumbRight, InputState::Active, ControllerID::Two }));
			m_GamepadCommands.push_back(input.AddGamepadCommand(std::make_unique<MoveCommand>(GetGameObject(), glm::vec2{ -1, 0 }, walkSpeed),
				InputGamepadBinding{ Gamepad::Button::DpadLeft, InputState::Active, ControllerID::Two }));
			m_GamepadCommands.push_back(input.AddGamepadCommand(std::make_unique<MoveCommand>(GetGameObject(), glm::vec2{ 1, 0 }, walkSpeed),
				InputGamepadBinding{ Gamepad::Button::DpadRight, InputState::Active, ControllerID::Two }));
		}
	}

	// Set upwards movement
	m_pMoveCommand = std::make_unique<MoveCommand>(GetGameObject(), glm::vec2{ 0, 1 }, 100.f);
}

void DragonPlayerStateJumping::OnExit()
{
	auto& input = InputManager::GetInstance();
	for (auto pCommand : m_KeyboardCommands)
	{
		input.RemoveKeyboardCommand(pCommand);
	}
	for (auto pCommand : m_GamepadCommands)
	{
		input.RemoveGamepadCommand(pCommand);
	}
}

void DragonPlayerStateJumping::Update()
{
	m_AccuSec += TimeManager::GetInstance().GetDeltaTime();

	if (m_AccuSec >= m_JumpTime)
	{
		m_IsFalling = true;
	}
	else
	{
		m_pMoveCommand->Execute();
	}
}

std::unique_ptr<State> DragonPlayerStateJumping::Transition()
{
	if (m_IsFalling) return std::make_unique<DragonPlayerStateFalling>(GetGameObject());
	return nullptr;
}


//-----------------------------------------------------------------
// DragonPlayerStateFalling Functions
//-----------------------------------------------------------------
void DragonPlayerStateFalling::OnEnter()
{
	// Set sprite
	{
		auto pSprite = ResourceManager::GetInstance().LoadSprite("BubbleBobble/Sprites/Dragon/Fall_Anim.png");
		auto pRenderer = GetGameObject()->GetComponentInChildren<CSpriteRenderer>();
		pRenderer->SetSprite(pSprite, 10.f / 60.f);
	}

	// Get Entity collision
	m_pEntityCollision = GetGameObject()->GetComponent<EntityCollision>();

	// Set commands
	{
		auto& input = InputManager::GetInstance();
		auto pDragon = GetGameObject()->GetComponent<Dragon>();
		float walkSpeed{ 40.f };

		if (pDragon->GetPlayerIdx() == Player::One)
		{
			// Keyboard
			m_KeyboardCommands.push_back(input.AddKeyboardCommand(std::make_unique<MoveCommand>(GetGameObject(), glm::vec2{ -1, 0 }, walkSpeed),
				InputKeyboardBinding{ Keyboard::Key::SDL_SCANCODE_A, InputState::Active }));
			m_KeyboardCommands.push_back(input.AddKeyboardCommand(std::make_unique<MoveCommand>(GetGameObject(), glm::vec2{ 1, 0 }, walkSpeed),
				InputKeyboardBinding{ Keyboard::Key::SDL_SCANCODE_D, InputState::Active }));

			// Gamepad
			m_GamepadCommands.push_back(input.AddGamepadCommand(std::make_unique<MoveCommand>(GetGameObject(), glm::vec2{ -1, 0 }, walkSpeed),
				InputGamepadBinding{ Gamepad::Button::LeftThumbLeft, InputState::Active, ControllerID::One }));
			m_GamepadCommands.push_back(input.AddGamepadCommand(std::make_unique<MoveCommand>(GetGameObject(), glm::vec2{ 1, 0 }, walkSpeed),
				InputGamepadBinding{ Gamepad::Button::LeftThumbRight, InputState::Active, ControllerID::One }));
			m_GamepadCommands.push_back(input.AddGamepadCommand(std::make_unique<MoveCommand>(GetGameObject(), glm::vec2{ -1, 0 }, walkSpeed),
				InputGamepadBinding{ Gamepad::Button::DpadLeft, InputState::Active, ControllerID::One }));
			m_GamepadCommands.push_back(input.AddGamepadCommand(std::make_unique<MoveCommand>(GetGameObject(), glm::vec2{ 1, 0 }, walkSpeed),
				InputGamepadBinding{ Gamepad::Button::DpadRight, InputState::Active, ControllerID::One }));
		}
		else if (pDragon->GetPlayerIdx() == Player::Two)
		{
			// Keyboard
			m_KeyboardCommands.push_back(input.AddKeyboardCommand(std::make_unique<MoveCommand>(GetGameObject(), glm::vec2{ -1, 0 }, walkSpeed),
				InputKeyboardBinding{ Keyboard::Key::SDL_SCANCODE_LEFT, InputState::Active }));
			m_KeyboardCommands.push_back(input.AddKeyboardCommand(std::make_unique<MoveCommand>(GetGameObject(), glm::vec2{ 1, 0 }, walkSpeed),
				InputKeyboardBinding{ Keyboard::Key::SDL_SCANCODE_RIGHT, InputState::Active }));

			// Gamepad
			m_GamepadCommands.push_back(input.AddGamepadCommand(std::make_unique<MoveCommand>(GetGameObject(), glm::vec2{ -1, 0 }, walkSpeed),
				InputGamepadBinding{ Gamepad::Button::LeftThumbLeft, InputState::Active, ControllerID::Two }));
			m_GamepadCommands.push_back(input.AddGamepadCommand(std::make_unique<MoveCommand>(GetGameObject(), glm::vec2{ 1, 0 }, walkSpeed),
				InputGamepadBinding{ Gamepad::Button::LeftThumbRight, InputState::Active, ControllerID::Two }));
			m_GamepadCommands.push_back(input.AddGamepadCommand(std::make_unique<MoveCommand>(GetGameObject(), glm::vec2{ -1, 0 }, walkSpeed),
				InputGamepadBinding{ Gamepad::Button::DpadLeft, InputState::Active, ControllerID::Two }));
			m_GamepadCommands.push_back(input.AddGamepadCommand(std::make_unique<MoveCommand>(GetGameObject(), glm::vec2{ 1, 0 }, walkSpeed),
				InputGamepadBinding{ Gamepad::Button::DpadRight, InputState::Active, ControllerID::Two }));
		}
	}

	// Set downwards movement
	m_pMoveCommand = std::make_unique<MoveCommand>(GetGameObject(), glm::vec2{ 0, -1 }, 80.f);
}

void DragonPlayerStateFalling::OnExit()
{
	auto& input = InputManager::GetInstance();
	for (auto pCommand : m_KeyboardCommands)
	{
		input.RemoveKeyboardCommand(pCommand);
	}
	for (auto pCommand : m_GamepadCommands)
	{
		input.RemoveGamepadCommand(pCommand);
	}
}

void DragonPlayerStateFalling::Update()
{
	m_pMoveCommand->Execute();
}

std::unique_ptr<State> DragonPlayerStateFalling::Transition()
{
	if (m_pEntityCollision->IsGoingDown()) return nullptr;
	return std::make_unique<DragonPlayerStateIdle>(GetGameObject());
}


//-----------------------------------------------------------------
// DragonPlayerStateDeath Functions
//-----------------------------------------------------------------
void DragonPlayerStateDeath::OnEnter()
{
	// Set sprite
	{
		auto pSprite = ResourceManager::GetInstance().LoadSprite("BubbleBobble/Sprites/Dragon/Death_Anim1.png");
		auto pRenderer = GetGameObject()->GetComponentInChildren<CSpriteRenderer>();
		pRenderer->Unlock();
		pRenderer->SetSprite(pSprite, 3.f / 60.f);
		pRenderer->Pause(m_FirstFrameTime);
		m_Timer = m_FirstFrameTime + m_DeathAnim1Time;
	}

	// Play sound
	Locator::GetSoundSystem().Play("BubbleBobble/Audio/PlayerDeath.wav", 1.f);
}

void DragonPlayerStateDeath::OnExit()
{
	//todo: notify lives component that player is dead
}

void DragonPlayerStateDeath::Update()
{
	m_AccuSec += TimeManager::GetInstance().GetDeltaTime();

	if (m_AccuSec >= m_Timer)
	{
		if (m_IsAnim2)
		{
			m_NeedsRespawn = true;
			GetGameObject()->GetComponentInChildren<CSpriteRenderer>()->SetSprite(nullptr);
		}
		else
		{
			m_IsAnim2 = true;
			auto pSprite = ResourceManager::GetInstance().LoadSprite("BubbleBobble/Sprites/Dragon/Death_Anim2.png");
			auto pRenderer = GetGameObject()->GetComponentInChildren<CSpriteRenderer>();
			pRenderer->SetSprite(pSprite, 3.f / 60.f);
		}

		m_AccuSec -= m_Timer;
	}
}

std::unique_ptr<State> DragonPlayerStateDeath::Transition()
{
	if (m_NeedsRespawn) return std::make_unique<DragonPlayerStateIdle>(GetGameObject());
	return nullptr;
}


//-----------------------------------------------------------------
// DragonPlayerStateWin Functions
//-----------------------------------------------------------------
void DragonPlayerStateWin::OnEnter()
{
	// Get dragon for easy access to data needed in update
	m_pDragonOwner = GetGameObject()->GetComponent<Dragon>();

	// Get Entity collision
	m_pEntityCollision = GetGameObject()->GetComponent<EntityCollision>();
	m_pEntityCollision->SetPlatformCollision(false);
	m_pEntityCollision->SetStaticLevelCollision(false);

	// Set sprite
	{
		auto pSprite = ResourceManager::GetInstance().LoadSprite("BubbleBobble/Sprites/Dragon/Win_Anim1.png");
		m_pRenderer = GetGameObject()->GetComponentInChildren<CSpriteRenderer>();
		m_pRenderer->Unlock();
		m_pRenderer->SetSprite(pSprite, 10.f / 60.f);
	}

	// Set delegates
	m_AnimationEndHandle = m_pRenderer->AnimationLooped.AddFunction(std::bind(&DragonPlayerStateWin::OnAnimationEnd, this));

	// Set movement to start pos
	m_pMoveCommand = std::make_unique<MoveCommand>(
		GetGameObject(),
		glm::normalize(m_pDragonOwner->GetStartPosition() - GetGameObject()->GetTransform().GetLocalPosition()),
		60.f);
}

void DragonPlayerStateWin::OnExit()
{
	// Remove delegates
	if (m_AnimationEndHandle.IsValid()) m_pRenderer->AnimationLooped.Remove(m_AnimationEndHandle);

	m_pEntityCollision->SetPlatformCollision(true);
	m_pEntityCollision->SetStaticLevelCollision(true);
}

void DragonPlayerStateWin::Update()
{
	if (!m_IsAtStartPos)
	{
		m_pMoveCommand->Execute();
		float dotProduct = glm::dot(m_pMoveCommand->GetDirection(),
			glm::normalize(m_pDragonOwner->GetStartPosition() - GetGameObject()->GetTransform().GetLocalPosition()));

		// If the angle is bigger than 90 degrees we have passed our target
		if (dotProduct <= 0.f)
		{
			m_IsAtStartPos = true;
			GetGameObject()->GetTransform().SetLocalPosition(m_pDragonOwner->GetStartPosition());
		}
	}

	// Only if animation 1 has finished can the player respawn
	if (m_CurrentAnim == 2 && m_IsAtStartPos && m_pDragonOwner->GetIsLevelLoaded())
	{
		m_pRenderer->SetSprite(ResourceManager::GetInstance().LoadSprite("BubbleBobble/Sprites/Dragon/Win_Anim3.png"), 4.f / 60.f);
		m_CurrentAnim = 3;
	}
}

std::unique_ptr<State> DragonPlayerStateWin::Transition()
{
	if (m_NeedsRespawn) return std::make_unique<DragonPlayerStateIdle>(GetGameObject());
	return nullptr;
}

void DragonPlayerStateWin::OnAnimationEnd()
{
	if (m_CurrentAnim == 1)
	{
		m_pRenderer->SetSprite(ResourceManager::GetInstance().LoadSprite("BubbleBobble/Sprites/Dragon/Win_Anim2.png"), 10.f / 60.f);
		m_CurrentAnim = 2;
	}
	else if (m_CurrentAnim == 3)
	{
		m_pRenderer->SetSprite(nullptr);
		m_NeedsRespawn = true;
	}
}
