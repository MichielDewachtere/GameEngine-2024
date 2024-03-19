#include "TextComponent.h"

#include <SDL_ttf.h>

#include <stdexcept>

#include "Renderer.h"
#include "GameObject.h"
#include "Logger.h"
#include "ResourceManager.h"
#include "TextureComponent.h"

dae::TextComponent::TextComponent(GameObject* pOwner, std::string text, std::unique_ptr<Font> pFont,
                                  const glm::u8vec4& color)
	: Component(pOwner)
	, m_Text(std::move(text))
	, m_Color(color)
	, m_pFont(std::move(pFont))
{
}

//dae::TextComponent::TextComponent(GameObject* pOwner, std::string text, std::string fontPath, int fontSize,
//                                  const glm::u8vec4& color)
//	: Component(pOwner)
//	, m_Text(std::move(text))
//	, m_Color(color)
//	, m_pFont(nullptr)
//{
//	m_pFont = ResourceManager::GetInstance().LoadFont(fontPath, fontSize);
//}

void dae::TextComponent::Start()
{
	m_pTextureComponent = GetOwner()->GetComponent<TextureComponent>();
	if (m_pTextureComponent == nullptr)
	{
		// TODO: this crashes out if text component is not last in component list
		m_pTextureComponent = GetOwner()->AddComponent<TextureComponent>(nullptr);
	}
}

void dae::TextComponent::LateUpdate()
{
	if (m_IsDirty)
	{
		if (m_pFont == nullptr)
			Logger::LogWarning({ "No font selected in text component" });

		if (m_Text.empty())
			Logger::LogWarning({ "No text in text component" });

		const auto surf = TTF_RenderText_Blended(m_pFont->GetFont(), m_Text.c_str(), { m_Color.r, m_Color.g, m_Color.b, m_Color.a });
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

		m_pTextureComponent->SetTexture(std::make_unique<Texture2D>(texture));
		m_IsDirty = false;
	}
}

void dae::TextComponent::SetText(const std::string& text)
{
	m_Text = text;
	m_IsDirty = true;
}

void dae::TextComponent::SetFont(std::unique_ptr<Font> pFont)
{
	m_pFont = std::move(pFont);
	m_IsDirty = true;
}

void dae::TextComponent::SetFont(const std::string& fontPath, int size)
{
	m_pFont = ResourceManager::GetInstance().LoadFont(fontPath, size);
	m_IsDirty = true;
}

void dae::TextComponent::SetColor(const glm::u8vec4& color)
{
	m_Color = color;
	m_IsDirty = true;
}
