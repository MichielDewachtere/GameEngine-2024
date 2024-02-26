#ifndef TEXTCOMPONENT_H
#define TEXTCOMPONENT_H

#include "DrawableComponent.h"

namespace dae
{
	class Font;
	class Texture2D;
	class TextComponent final : public DrawableComponent
	{
	public:
		explicit TextComponent(GameObject* pOwner, std::string text = "", std::shared_ptr<Font> pFont = nullptr,
		                       const SDL_Color& color = {255, 255, 255, 255});
		explicit TextComponent(GameObject* pOwner, std::string text = "", std::string fontPath = "", int fontSize = 16,
		                       const SDL_Color& color = {255, 255, 255, 255});
		virtual ~TextComponent() override = default;

		TextComponent(const TextComponent& other) = delete;
		TextComponent& operator=(const TextComponent& other) = delete;
		TextComponent(TextComponent&& other) = delete;
		TextComponent& operator=(TextComponent&& other) = delete;

		virtual void LateUpdate() override;
		virtual void Render() override;

		void SetText(const std::string& text);
		const std::string& GetText() const { return m_Text; }

		void SetFont(const std::shared_ptr<Font>& pFont);
		void SetFont(const std::string& fontPath, int size);
		void SetColor(const SDL_Color& color);

	private:
		bool m_IsDirty{ true };
		std::string m_Text;
		SDL_Color m_Color;

		std::shared_ptr<Font> m_pFont;
		// TODO: ADD TextureComponent
		std::shared_ptr<Texture2D> m_pTextTexture;
	};
}

#endif // TEXTCOMPONENT_H