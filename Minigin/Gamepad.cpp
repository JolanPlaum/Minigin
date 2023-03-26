//-----------------------------------------------------------------
// Includes
//-----------------------------------------------------------------
#include "Gamepad.h"
#include <Windows.h>
#include <Xinput.h>

using namespace dae;


//-----------------------------------------------------------------
// Implementation
//-----------------------------------------------------------------
class Gamepad::GamepadImpl final
{
	int controllerId;

	XINPUT_STATE inputState{};
	
	unsigned int active;
	unsigned int pressed;
	unsigned int released;

public:
	GamepadImpl(int controllerIndex)
		: controllerId{ controllerIndex }
	{
	}

	void Update()
	{
		// Get the current state of XInput
		XINPUT_STATE currentState{};
		ZeroMemory(&currentState, sizeof(XINPUT_STATE));
		DWORD dwResult = XInputGetState(controllerId, &currentState);
		if (dwResult != ERROR_SUCCESS)
		{
			ZeroMemory(&inputState, sizeof(XINPUT_STATE));
			active = 0;
			pressed = 0;
			released = 0;
			return;
		}

		// Casting bool to int and making it negative will turn all the bits into either 1 or 0
		// Get the current buttons
		unsigned int currentActiveButtons = currentState.Gamepad.wButtons;
		currentActiveButtons |= static_cast<unsigned int>(Button::LeftTrigger) & -static_cast<int>(currentState.Gamepad.bLeftTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD);
		currentActiveButtons |= static_cast<unsigned int>(Button::RightTrigger) & -static_cast<int>(currentState.Gamepad.bRightTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD);

		currentActiveButtons |= static_cast<unsigned int>(Button::LeftThumbUp) & -static_cast<int>(currentState.Gamepad.sThumbLY > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE);
		currentActiveButtons |= static_cast<unsigned int>(Button::LeftThumbDown) & -static_cast<int>(currentState.Gamepad.sThumbLY < -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE);
		currentActiveButtons |= static_cast<unsigned int>(Button::LeftThumbLeft) & -static_cast<int>(currentState.Gamepad.sThumbLX < -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE);
		currentActiveButtons |= static_cast<unsigned int>(Button::LeftThumbRight) & -static_cast<int>(currentState.Gamepad.sThumbLX > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE);

		currentActiveButtons |= static_cast<unsigned int>(Button::RightThumbUp) & -static_cast<int>(currentState.Gamepad.sThumbRY > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE);
		currentActiveButtons |= static_cast<unsigned int>(Button::RightThumbDown) & -static_cast<int>(currentState.Gamepad.sThumbRY < -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE);
		currentActiveButtons |= static_cast<unsigned int>(Button::RightThumbLeft) & -static_cast<int>(currentState.Gamepad.sThumbRX < -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE);
		currentActiveButtons |= static_cast<unsigned int>(Button::RightThumbRight) & -static_cast<int>(currentState.Gamepad.sThumbRX > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE);

		// Update data
		auto buttonChanges = currentActiveButtons ^ active;
		pressed = buttonChanges & currentActiveButtons;
		released = buttonChanges & active;
		active = currentActiveButtons;

		// Store the state for axis values
		CopyMemory(&inputState, &currentState, sizeof(XINPUT_STATE));
	}

	bool IsPressed(unsigned int button) const { return pressed & button; }
	bool IsReleased(unsigned int button) const { return released & button; }
	bool IsActive(unsigned int button) const { return active & button; }
};


//-----------------------------------------------------------------
// Constructors
//-----------------------------------------------------------------
Gamepad::Gamepad(int controllerIndex)
{
	m_pImpl = std::make_unique<GamepadImpl>(controllerIndex);
}


//-----------------------------------------------------------------
// Destructor
//-----------------------------------------------------------------
Gamepad::~Gamepad()
{
}


//-----------------------------------------------------------------
// Public Member Functions
//-----------------------------------------------------------------
void Gamepad::Update()
{
	m_pImpl->Update();
}

bool Gamepad::IsPressed(Button button)
{
	return m_pImpl->IsPressed(static_cast<unsigned int>(button));
}

bool Gamepad::IsReleased(Button button)
{
	return m_pImpl->IsReleased(static_cast<unsigned int>(button));
}

bool Gamepad::IsActive(Button button)
{
	return m_pImpl->IsActive(static_cast<unsigned int>(button));
}


//-----------------------------------------------------------------
// Private Member Functions
//-----------------------------------------------------------------

