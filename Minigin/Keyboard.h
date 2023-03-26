#pragma once
// Includes
#define WIN32_LEAN_AND_MEAN 
#include <windows.h>
#include <memory>
#include <SDL_scancode.h>

namespace dae
{
	// Class Forward Declarations
	
	// Class Declaration
	class Keyboard final
	{
	public:
		// Constructors and Destructor
		explicit Keyboard();
		~Keyboard();
		
		// Copy and Move semantics
		Keyboard(const Keyboard& other)					= delete;
		Keyboard& operator=(const Keyboard& other)		= delete;
		Keyboard(Keyboard&& other) noexcept				= delete;
		Keyboard& operator=(Keyboard&& other) noexcept	= delete;
		
		//---------------------------
		// Public Member Functions
		//---------------------------
		using Key = SDL_Scancode;

		void Update();

		bool IsPressed(Key button);
		bool IsReleased(Key button);
		bool IsActive(Key button);
		
		
	private:
		// Member variables
		class KeyboardImpl;
		std::unique_ptr<KeyboardImpl> m_pImpl;
		
		//---------------------------
		// Private Member Functions
		//---------------------------
	
	};
}

