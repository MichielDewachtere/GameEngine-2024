#ifndef TEXTCOMPONENT_H
#define TEXTCOMPONENT_H

#include <memory>
#include <string>

#include <glm/vec4.hpp>

#include "Component.h"
#include "Font.h"
#include "TextComponent.h"

namespace real
{
	enum class HorizontalTextAlignment : char
	{
		left,
		right,
		center,
	};
	enum class VerticalTextAlignment : char
	{
		up,
		down,
		center,
	};

	struct TextInfo
	{
		std::unique_ptr<Font> pFont{ nullptr };
		std::string text{ "empty" };
		glm::u8vec4 color{ 255,255,255,255 };
		HorizontalTextAlignment horizontalAlignment{ HorizontalTextAlignment::right };
		VerticalTextAlignment verticalAlignment{ VerticalTextAlignment::down };
	};

	class TextureComponent;

	class TextComponent final : public Component
	{
	public:

		explicit TextComponent(GameObject* pOwner, TextInfo info = {});
		virtual ~TextComponent() override = default;

		TextComponent(const TextComponent& other) = delete;
		TextComponent& operator=(const TextComponent& other) = delete;
		TextComponent(TextComponent&& other) = delete;
		TextComponent& operator=(TextComponent&& other) = delete;

		void Start() override;

		virtual void LateUpdate() override;

		void SetText(const std::string& text);
		const std::string& GetText() const { return m_Text; }

		void SetFont(std::unique_ptr<Font> pFont);
		void SetFont(const std::string& fontPath, int size);

		void SetColor(const glm::u8vec4& color);
		glm::u8vec4 GetColor() const { return m_Color; }

		void SetHorizontalAlignment(HorizontalTextAlignment alignment);
		void SetVerticalAlignment(VerticalTextAlignment alignment);

	private:
		bool m_IsDirty{ true };
		std::string m_Text;
		glm::u8vec4 m_Color;
		glm::vec2 m_RenderOffset{};
		HorizontalTextAlignment m_HorizontalAlignment;
		VerticalTextAlignment m_VerticalAlignment;

		std::unique_ptr<Font> m_pFont;
		TextureComponent* m_pTextureComponent{ nullptr };

		float HandleHorizontalAlignment() const;
		float HandleVerticalAlignment() const;
	};
}

#endif // TEXTCOMPONENT_H