#include <stdexcept>
#include "Renderer.h"
#include "SceneManager.h"
#include "Texture2D.h"
#include "GuiManager.h"

int GetOpenGLDriverIndex()
{
	auto openglIndex = -1;
	const auto driverCount = SDL_GetNumRenderDrivers();
	for (auto i = 0; i < driverCount; i++)
	{
		SDL_RendererInfo info;
		if (!SDL_GetRenderDriverInfo(i, &info))
			if (!strcmp(info.name, "opengl"))
				openglIndex = i;
	}
	return openglIndex;
}

void dae::Renderer::Init(SDL_Window* window)
{
	m_window = window;
	m_renderer = SDL_CreateRenderer(window, GetOpenGLDriverIndex(), SDL_RENDERER_ACCELERATED);
	if (m_renderer == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateRenderer Error: ") + SDL_GetError());
	}

	int temp;
	SDL_GetRendererOutputSize(m_renderer, &temp, &m_WindowHeight);
}

void dae::Renderer::Render() const
{
	const auto& color = GetBackgroundColor();
	SDL_SetRenderDrawColor(m_renderer, color.r, color.g, color.b, color.a);
	SDL_RenderClear(m_renderer);

	SceneManager::GetInstance().Render();

	GuiManager::GetInstance().RenderGui();
	
	SDL_RenderPresent(m_renderer);
}

void dae::Renderer::Destroy()
{
	if (m_renderer != nullptr)
	{
		SDL_DestroyRenderer(m_renderer);
		m_renderer = nullptr;
	}
}

void dae::Renderer::RenderTexture(const Texture2D& texture, float x, float y) const
{
	SDL_Rect dst{};
	SDL_QueryTexture(texture.GetSDLTexture(), nullptr, nullptr, &dst.w, &dst.h);

	RenderTexture(texture, x, y, static_cast<float>(dst.w), static_cast<float>(dst.h));
}

void dae::Renderer::RenderTexture(const Texture2D& texture, float x, float y, float width, float height) const
{
	SDL_Rect dst{};
	dst.w = static_cast<int>(abs(width));
	dst.h = static_cast<int>(abs(height));
	dst.x = static_cast<int>(x);
	dst.y = m_WindowHeight - dst.h - static_cast<int>(y);

	int flip{};
	if (width < 0.f) flip |= SDL_FLIP_HORIZONTAL;
	if (height < 0.f) flip |= SDL_FLIP_VERTICAL;

	SDL_RenderCopyEx(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst, 0, nullptr, static_cast<SDL_RendererFlip>(flip));
}

void dae::Renderer::RenderTexture(const Texture2D& texture, const Rectangle& dstRect, const Rectangle& srcRect) const
{
	SDL_Rect dst{}, src{};
	dst.w = static_cast<int>(abs(dstRect.w));
	dst.h = static_cast<int>(abs(dstRect.h));
	dst.x = static_cast<int>(dstRect.x);
	dst.y = m_WindowHeight - dst.h - static_cast<int>(dstRect.y);

	src.x = static_cast<int>(srcRect.x);
	src.y = static_cast<int>(srcRect.y);
	src.w = static_cast<int>(srcRect.w);
	src.h = static_cast<int>(srcRect.h);

	int flip{};
	if (dstRect.w < 0.f) flip |= SDL_FLIP_HORIZONTAL;
	if (dstRect.h < 0.f) flip |= SDL_FLIP_VERTICAL;

	SDL_RenderCopyEx(GetSDLRenderer(), texture.GetSDLTexture(), &src, &dst, 0, nullptr, static_cast<SDL_RendererFlip>(flip));
}

inline SDL_Renderer* dae::Renderer::GetSDLRenderer() const { return m_renderer; }
