#pragma once
// Includes
#include "CTexture.h"
#include <memory>
#include <string>
#include <SDL.h>

namespace dae
{
	// Class Forward Declarations
	class Font;
	
	// Class Declaration
	class CTextTexture : public CTexture
	{
	public:
		// Constructors and Destructor
		CTextTexture() = default;
		virtual ~CTextTexture() = default;
		
		// Copy and Move semantics
		CTextTexture(const CTextTexture& other)					= delete;
		CTextTexture& operator=(const CTextTexture& other)		= delete;
		CTextTexture(CTextTexture&& other) noexcept				= delete;
		CTextTexture& operator=(CTextTexture&& other) noexcept	= delete;
	
		//---------------------------
		// Public Member Functions
		//---------------------------
		void Update() override;

		void SetText(const std::string& text);
		void SetFont(std::shared_ptr<Font> font);
		void SetColor(const SDL_Color& color);
		void SetColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a = 255);
	
	
	private:
		// Member variables
		bool m_NeedsUpdate{};
		std::string m_Text{" "};
		std::shared_ptr<Font> m_pFont{};
		SDL_Color m_Color{ 255,255,255 };
	
		//---------------------------
		// Private Member Functions
		//---------------------------
	
	};
}

