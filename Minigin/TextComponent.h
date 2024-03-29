#ifndef TEXTCOMPONENT_H
#define TEXTCOMPONENT_H

#include <memory>
#include <string>

#include <glm/vec4.hpp>

#include "Component.h"
#include "Font.h"

namespace dae
{
	class TextureComponent;

	class TextComponent final : public Component
	{
	public:
		enum class HorizontalAlignment : char
		{
			left,
			right,
			center, 
		};
		enum class VerticalAlignment : char
		{
			up,
			down,
			center, 
		};

		explicit TextComponent(GameObject* pOwner, std::string text = "", std::unique_ptr<Font> pFont = nullptr,
		                       const glm::u8vec4& color = {255, 255, 255, 255});
		//explicit TextComponent(GameObject* pOwner, std::string text = "", std::string fontPath = "", int fontSize = 16,
		//                       const glm::u8vec4& color = {255, 255, 255, 255});
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
		void SetHorizontalAlignment(HorizontalAlignment alignment);
		void SetVerticalAlignment(VerticalAlignment alignment);

	private:
		bool m_IsDirty{ true };
		std::string m_Text;
		glm::u8vec4 m_Color;
		glm::vec2 m_RenderOffset{};
		HorizontalAlignment m_HorizontalAlignment{ HorizontalAlignment::right };
		VerticalAlignment m_VerticalAlignment{ VerticalAlignment::down };

		std::unique_ptr<Font> m_pFont;
		TextureComponent* m_pTextureComponent;

		float HandleHorizontalAlignment() const;
		float HandleVerticalAlignment() const;
	};
}

#endif // TEXTCOMPONENT_H