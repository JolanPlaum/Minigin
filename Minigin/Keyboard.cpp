//-----------------------------------------------------------------
// Includes
//-----------------------------------------------------------------
#include "Keyboard.h"
#include <SDL.h>
#include <vector>
#include <algorithm>
#include <functional>

using namespace dae;


//-----------------------------------------------------------------
// Implementation
//-----------------------------------------------------------------
class Keyboard::KeyboardImpl final
{
	std::vector<Uint8> active;
	std::vector<Uint8> pressed;
	std::vector<Uint8> released;

public:
	KeyboardImpl()
	{
		int nrKeys{};
		SDL_GetKeyboardState(&nrKeys);
		active.resize(nrKeys);
		pressed.resize(nrKeys);
		released.resize(nrKeys);
	}

	void Update()
	{
		// Get the current state of keyboard
		int nrKeys{};
		auto keyboardState = SDL_GetKeyboardState(&nrKeys);
		std::vector<Uint8> currActive(keyboardState, keyboardState + nrKeys);

		// Update data
		std::vector<Uint8> keyChanges(currActive.size());
		std::transform(currActive.begin(), currActive.end(), active.begin(), keyChanges.begin(), std::bit_xor<Uint8>());
		std::transform(keyChanges.begin(), keyChanges.end(), currActive.begin(), pressed.begin(), std::bit_and<Uint8>());
		std::transform(keyChanges.begin(), keyChanges.end(), active.begin(), released.begin(), std::bit_and<Uint8>());
		active = std::move(currActive);
	}

	bool IsPressed(unsigned int button) const { return pressed[button]; }
	bool IsReleased(unsigned int button) const { return released[button]; }
	bool IsActive(unsigned int button) const { return active[button]; }
};


//-----------------------------------------------------------------
// Constructors
//-----------------------------------------------------------------
Keyboard::Keyboard()
{
	m_pImpl = std::make_unique<KeyboardImpl>();
}


//-----------------------------------------------------------------
// Destructor
//-----------------------------------------------------------------
Keyboard::~Keyboard()
{
}


//-----------------------------------------------------------------
// Public Member Functions
//-----------------------------------------------------------------
void Keyboard::Update()
{
	m_pImpl->Update();
}

bool Keyboard::IsPressed(Key button)
{
	return m_pImpl->IsPressed(static_cast<unsigned int>(button));
}

bool Keyboard::IsReleased(Key button)
{
	return m_pImpl->IsReleased(static_cast<unsigned int>(button));
}

bool Keyboard::IsActive(Key button)
{
	return m_pImpl->IsActive(static_cast<unsigned int>(button));
}


//-----------------------------------------------------------------
// Private Member Functions
//-----------------------------------------------------------------

