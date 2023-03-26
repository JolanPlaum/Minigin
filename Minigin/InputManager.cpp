//-----------------------------------------------------------------
// Includes
//-----------------------------------------------------------------
#include "InputManager.h"
#include <SDL.h>
#include <Xinput.h>
#include <backends/imgui_impl_sdl2.h>

using namespace dae;


//-----------------------------------------------------------------
// Constructors
//-----------------------------------------------------------------
InputManager::InputManager()
{
	m_Keyboard = std::make_unique<Keyboard>();

	m_Gamepads.reserve(XUSER_MAX_COUNT);
	for (int i{}; i < XUSER_MAX_COUNT; ++i)
	{
		m_Gamepads.push_back(std::make_unique<Gamepad>(i));
	}
}


//-----------------------------------------------------------------
// Destructor
//-----------------------------------------------------------------


//-----------------------------------------------------------------
// Public Member Functions
//-----------------------------------------------------------------
bool InputManager::ProcessInput()
{
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			return false;
		}
		
		//process event for ImGui
		ImGui_ImplSDL2_ProcessEvent(&e);
	}

	m_Keyboard->Update();
	for (const auto& controller : m_Gamepads)
	{
		controller->Update();
	}

	HandleKeyboardInput();
	HandleGamepadInput();

	return true;
}

void InputManager::AddKeyboardCommand(std::unique_ptr<Command> pCommand, const InputKeyboardBinding& binding)
{
	if (pCommand == nullptr) return;

	m_KeyboardCommands.push_back(KeyboardCommand{ binding, std::move(pCommand) });
}

void InputManager::AddGamepadCommand(std::unique_ptr<Command> pCommand, const InputGamepadBinding& binding)
{
	if (pCommand == nullptr) return;

	m_GamepadCommands.push_back(GamepadCommand{ binding, std::move(pCommand) });
}
 

//-----------------------------------------------------------------
// Private Member Functions
//-----------------------------------------------------------------
void InputManager::HandleKeyboardInput()
{
	for (const auto& command : m_KeyboardCommands)
	{
		switch (command.first.inputState)
		{
		case InputState::Pressed:
			if (m_Keyboard->IsPressed(command.first.key))
				command.second->Execute();
			break;
		case InputState::Released:
			if (m_Keyboard->IsReleased(command.first.key))
				command.second->Execute();
			break;
		case InputState::Active:
			if (m_Keyboard->IsActive(command.first.key))
				command.second->Execute();
			break;
		}
	}
}

void InputManager::HandleGamepadInput()
{
	for (const auto& command : m_GamepadCommands)
	{
		switch (command.first.inputState)
		{
		case InputState::Pressed:
			if (m_Gamepads[static_cast<int>(command.first.controllerId)]->IsPressed(command.first.button))
				command.second->Execute();
			break;
		case InputState::Released:
			if (m_Gamepads[static_cast<int>(command.first.controllerId)]->IsReleased(command.first.button))
				command.second->Execute();
			break;
		case InputState::Active:
			if (m_Gamepads[static_cast<int>(command.first.controllerId)]->IsActive(command.first.button))
				command.second->Execute();
			break;
		}
	}
}

