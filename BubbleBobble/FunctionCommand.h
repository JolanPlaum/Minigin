#pragma once
// Includes
#include "Command.h"
#include <functional>

namespace dae
{
	// Class Forward Declarations
	
	// Class Declaration
	class FunctionCommand final : public Command
	{
	public:
		// Constructors and Destructor
		explicit FunctionCommand(std::function<void()> function);
		~FunctionCommand() = default;
		
		// Copy and Move semantics
		FunctionCommand(const FunctionCommand& other)					= delete;
		FunctionCommand& operator=(const FunctionCommand& other)		= delete;
		FunctionCommand(FunctionCommand&& other) noexcept				= delete;
		FunctionCommand& operator=(FunctionCommand&& other) noexcept	= delete;
		
		//---------------------------
		// Public Member Functions
		//---------------------------
		void Execute() override;
		
		
	private:
		// Member variables
		std::function<void()> m_Function;
		
		//---------------------------
		// Private Member Functions
		//---------------------------
		
	};
}

