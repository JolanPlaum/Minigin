//-----------------------------------------------------------------
// Includes
//-----------------------------------------------------------------
#include "CTextTexture.h"
#include <SDL_ttf.h>
#include "Font.h"
#include "Renderer.h"
#include "Texture2D.h"

using namespace dae;


//-----------------------------------------------------------------
// Constructors
//-----------------------------------------------------------------


//-----------------------------------------------------------------
// Destructor
//-----------------------------------------------------------------


//-----------------------------------------------------------------
// Public Member Functions
//-----------------------------------------------------------------
void CTextTexture::Update()
{
	if (m_NeedsUpdate)
	{
		const auto surf = TTF_RenderText_Blended(m_pFont->GetFont(), m_Text.c_str(), m_Color);
		if (surf == nullptr)
		{
			throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
		}
		auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf);
		if (texture == nullptr)
		{
			throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
		}
		SDL_FreeSurface(surf);
		m_pTexture = std::make_shared<Texture2D>(texture);
		m_NeedsUpdate = false;
	}
}

void CTextTexture::SetText(const std::string& text)
{
	m_Text = text;
	m_NeedsUpdate = true;
}

void CTextTexture::SetFont(std::shared_ptr<Font> font)
{
	m_pFont = font;
	m_NeedsUpdate = true;
}

void CTextTexture::SetColor(const SDL_Color& color)
{
	m_Color = color;
	m_NeedsUpdate = true;
}

void CTextTexture::SetColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	SetColor({ r,g,b,a });
}


//-----------------------------------------------------------------
// Private Member Functions
//-----------------------------------------------------------------

