#include "stdafx.h"
#include "TextComponent.h"
#include "Renderer.h"
#include "Font.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Texture2D.h"

dae::TextComponent::TextComponent(GameObject* pOwner, std::string text, const std::shared_ptr<Font> pFont,
	const SDL_Color& color)
	: DrawableComponent(pOwner)
	, m_Text(std::move(text))
	, m_Color(color)
	, m_pFont(pFont)
	, m_pTextTexture(nullptr)
{
}

dae::TextComponent::TextComponent(GameObject* pOwner, std::string text, std::string fontPath, int fontSize,
                                  const SDL_Color& color)
	: DrawableComponent(pOwner)
	, m_Text(std::move(text))
	, m_Color(color)
	, m_pFont(nullptr)
	, m_pTextTexture(nullptr)
{
	m_pFont = ResourceManager::GetInstance().LoadFont(fontPath, fontSize);
}

void dae::TextComponent::LateUpdate()
{
	if (m_IsDirty)
	{
		if (m_pFont == nullptr)
			Logger::LogWarning({ "No font selected in text component" });

		if (m_Text.empty())
			Logger::LogWarning({ "No text in text component" });

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
		m_pTextTexture = std::make_shared<Texture2D>(texture);
		m_IsDirty = false;
	}
}
void dae::TextComponent::Render()
{
	if (m_pTextTexture == nullptr)
		return;

	const auto& pos = GetOwner()->GetTransform()->GetWorldPosition();
	Renderer::GetInstance().RenderTexture(*m_pTextTexture, pos.x, pos.y);
}

// This implementation uses the "dirty flag" pattern
void dae::TextComponent::SetText(const std::string& text)
{
	m_Text = text;
	m_IsDirty = true;
}

void dae::TextComponent::SetFont(const std::shared_ptr<Font>& pFont)
{
	m_pFont = pFont;
	m_IsDirty = true;
}

void dae::TextComponent::SetFont(const std::string& fontPath, int size)
{
	m_pFont = ResourceManager::GetInstance().LoadFont(fontPath, size);
	m_IsDirty = true;
}

void dae::TextComponent::SetColor(const SDL_Color& color)
{
	m_Color = color;
	m_IsDirty = true;
}
