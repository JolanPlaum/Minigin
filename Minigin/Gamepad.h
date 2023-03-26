#pragma once
// Includes
#include <memory>

namespace dae
{
	// Class Forward Declarations
	
	// Class Declaration
	class Gamepad final
	{
	public:
		// Constructors and Destructor
		explicit Gamepad(int controllerIndex);
		~Gamepad();
		
		// Copy and Move semantics
		Gamepad(const Gamepad& other)					= delete;
		Gamepad& operator=(const Gamepad& other)		= delete;
		Gamepad(Gamepad&& other) noexcept				= delete;
		Gamepad& operator=(Gamepad&& other) noexcept	= delete;
		
		//---------------------------
		// Public Member Functions
		//---------------------------
		enum class Button : unsigned int
		{
			None			= 0x0000,

			DpadUp			= 0x0001,
			DpadDown		= 0x0002,
			DpadLeft		= 0x0004,
			DpadRight		= 0x0008,

			SpecialLeft		= 0x0010,
			SpecialRight	= 0x0020,
			LeftThumb		= 0x0040,
			RightThumb		= 0x0080,

			LeftShoulder	= 0x0100,
			RightShoulder	= 0x0200,
			LeftTrigger		= 0x0400,
			RightTrigger	= 0x0800,

			ButtonDown		= 0x1000,
			ButtonRight		= 0x2000,
			ButtonLeft		= 0x4000,
			ButtonUp		= 0x8000,

			LeftThumbUp		= 0x0001'0000,
			LeftThumbDown	= 0x0002'0000,
			LeftThumbLeft	= 0x0004'0000,
			LeftThumbRight	= 0x0008'0000,

			RightThumbUp	= 0x0010'0000,
			RightThumbDown	= 0x0020'0000,
			RightThumbLeft	= 0x0040'0000,
			RightThumbRight	= 0x0080'0000,
		};

		void Update();

		bool IsPressed(Button button);
		bool IsReleased(Button button);
		bool IsActive(Button button);
		
		
	private:
		// Member variables
		class GamepadImpl;
		std::unique_ptr<GamepadImpl> m_pImpl;
		
		//---------------------------
		// Private Member Functions
		//---------------------------
	
	};
}

