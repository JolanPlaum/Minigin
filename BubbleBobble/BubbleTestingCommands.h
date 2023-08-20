#pragma once
// Includes
#include "Command.h"
#include <string>

namespace dae
{
	// Class Forward Declarations
	
	// Class Declaration
	class LaunchBubbleCommand final : public GameObjectCommand
	{
	public:
		// Constructors and Destructor
		explicit LaunchBubbleCommand(GameObject* pGameObject, std::string color);
		~LaunchBubbleCommand() = default;
		
		// Copy and Move semantics
		LaunchBubbleCommand(const LaunchBubbleCommand& other)					= delete;
		LaunchBubbleCommand& operator=(const LaunchBubbleCommand& other)		= delete;
		LaunchBubbleCommand(LaunchBubbleCommand&& other) noexcept				= delete;
		LaunchBubbleCommand& operator=(LaunchBubbleCommand&& other) noexcept	= delete;
		
		//---------------------------
		// Public Member Functions
		//---------------------------
		void Execute() override;
		
		
	private:
		// Member variables
		std::string m_Color{};
		
		//---------------------------
		// Private Member Functions
		//---------------------------
		
	};
}
