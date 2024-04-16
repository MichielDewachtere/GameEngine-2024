#include "Font.h"

#include <SDL_ttf.h>
#include <stdexcept>

#include "Renderer.h"

TTF_Font* real::Font::GetFont() const {
	return m_pFont;
}

std::unique_ptr<real::Texture2D> real::Font::CreateTexture(const std::string& text, glm::u8vec4 color) const
{
	const SDL_Color sdlColor{ color.r, color.g, color.b, color.a };
	const auto surf = TTF_RenderText_Blended(m_pFont, text.c_str(), sdlColor);
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

	return std::make_unique<Texture2D>(texture);
}

real::Font::Font(const std::string& fullPath, unsigned int size) : m_pFont(nullptr)
{
	m_pFont = TTF_OpenFont(fullPath.c_str(), size);
	if (m_pFont == nullptr) 
	{
		throw std::runtime_error(std::string("Failed to load font: ") + SDL_GetError());
	}
}

real::Font::~Font()
{
	TTF_CloseFont(m_pFont);
}
