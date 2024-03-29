#include "TextComponent.h"

#include <memory>
#include <stdexcept>

#include "Renderer.h"
#include "GameObject.h"
#include "Logger.h"
#include "ResourceManager.h"
#include "TextureComponent.h"
#include "Texture2D.h"

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

		auto i = m_pFont->CreateTexture(m_Text, m_Color);
		m_pTextureComponent->SetTexture(std::move(i));

		glm::vec2 renderOffset;
		renderOffset.x = HandleHorizontalAlignment();
		renderOffset.y = HandleVerticalAlignment();

		m_pTextureComponent->SetRenderOffset(renderOffset);

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

void dae::TextComponent::SetHorizontalAlignment(HorizontalAlignment alignment)
{
	m_HorizontalAlignment = alignment;
	m_IsDirty = true;
}

void dae::TextComponent::SetVerticalAlignment(VerticalAlignment alignment)
{
	m_VerticalAlignment = alignment;
	m_IsDirty = true;
}

float dae::TextComponent::HandleHorizontalAlignment() const
{
	const auto textureSize = m_pTextureComponent->GetTexture()->GetSize();
	float x = 0;

	switch (m_HorizontalAlignment)
	{
	case HorizontalAlignment::left:
	{
		x = static_cast<float>(textureSize.x);
		break;
	}
	case HorizontalAlignment::center:
	{
		x = static_cast<float>(textureSize.x) / 2.f;
		break;
	}
	case HorizontalAlignment::right:
	{
		x = 0;
		break;
	}
	}

	return x;
}

float dae::TextComponent::HandleVerticalAlignment() const
{
	const auto textureSize = m_pTextureComponent->GetTexture()->GetSize();
	float y = 0;

	switch (m_VerticalAlignment)
	{
	case VerticalAlignment::up:
	{
		y = static_cast<float>(textureSize.y);
		break;
	}
	case VerticalAlignment::center:
	{
		y = static_cast<float>(textureSize.y) / 2.f;
		break;
	}
	case VerticalAlignment::down:
	{
		y = 0;
		break;
	}
	}

	return y;
}
