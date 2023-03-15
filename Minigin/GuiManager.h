#pragma once
// Includes
#include "Singleton.h"
#include <SDL.h>

namespace dae
{
	// Class Forward Declarations
	
	// Class Declaration
	class GuiManager final : public Singleton<GuiManager>
	{
	public:
		// Constructors and Destructor
		~GuiManager() = default;
		
		// Copy and Move semantics
		GuiManager(const GuiManager& other)					= delete;
		GuiManager& operator=(const GuiManager& other)		= delete;
		GuiManager(GuiManager&& other) noexcept				= delete;
		GuiManager& operator=(GuiManager&& other) noexcept	= delete;
	
		//---------------------------
		// Public Member Functions
		//---------------------------
		void Init(SDL_Window* pWindow);
		void OnGui();
		void Destroy();
	
	
	private:
		// Member variables
		SDL_Window* m_pWindow{};
	
		//---------------------------
		// Private Member Functions
		//---------------------------
		friend class Singleton<GuiManager>;
		GuiManager() = default;
	
	};
}

