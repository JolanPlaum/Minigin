#pragma once
// Includes
#include "Component.h"

namespace dae
{
	// Class Forward Declarations
	class CTextTexture;
	
	// Class Declaration
	class FPS final : public BehaviourComponent
	{
	public:
		// Constructors and Destructor
		FPS() = default;
		~FPS() = default;
		
		// Copy and Move semantics
		FPS(const FPS& other)					= delete;
		FPS& operator=(const FPS& other)		= delete;
		FPS(FPS&& other) noexcept				= delete;
		FPS& operator=(FPS&& other) noexcept	= delete;
	
		//---------------------------
		// Public Member Functions
		//---------------------------
		void Init() override;
		void Update() override;
	
	
	private:
		// Member variables
		std::weak_ptr<CTextTexture> m_TextComponent{};
	
		//---------------------------
		// Private Member Functions
		//---------------------------
	
	};
}

