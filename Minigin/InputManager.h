#pragma once
// Includes
#include <vector>
#include <memory>
#include "Singleton.h"
#include "Keyboard.h"
#include "Gamepad.h"
#include "Command.h"

namespace dae
{
	// Class Forward Declarations
	enum class InputState : unsigned char
	{
		Pressed,
		Released,
		Active,
	};
	enum class ControllerID : unsigned char
	{
		One		= 0,
		Two		= 1,
		Three	= 2,
		Four	= 3,
	};
	struct InputKeyboardBinding
	{
		Keyboard::Key key;
		InputState inputState;
	};
	struct InputGamepadBinding
	{
		Gamepad::Button button;
		InputState inputState;
		ControllerID controllerId;
	};

	// Class Declaration
	class InputManager final : public Singleton<InputManager>
	{
	public:
		// Constructors and Destructor
		~InputManager() = default;
		
		// Copy and Move semantics
		InputManager(const InputManager& other)					= delete;
		InputManager& operator=(const InputManager& other)		= delete;
		InputManager(InputManager&& other) noexcept				= delete;
		InputManager& operator=(InputManager&& other) noexcept	= delete;
		
		//---------------------------
		// Public Member Functions
		//---------------------------
		bool ProcessInput();

		void AddKeyboardCommand(std::unique_ptr<Command> pCommand, const InputKeyboardBinding& binding);
		void AddGamepadCommand(std::unique_ptr<Command> pCommand, const InputGamepadBinding& binding);
		
		
	private:
		// Member variables
		std::unique_ptr<Keyboard> m_Keyboard{};
		std::vector<std::unique_ptr<Gamepad>> m_Gamepads{};

		using KeyboardCommand = std::pair<InputKeyboardBinding, std::unique_ptr<Command>>;
		std::vector<KeyboardCommand> m_KeyboardCommands{};

		using GamepadCommand = std::pair<InputGamepadBinding, std::unique_ptr<Command>>;
		std::vector<GamepadCommand> m_GamepadCommands{};
		
		//---------------------------
		// Private Member Functions
		//---------------------------
		friend class Singleton<InputManager>;
		InputManager();

		void HandleKeyboardInput();
		void HandleGamepadInput();
		
	};

}
