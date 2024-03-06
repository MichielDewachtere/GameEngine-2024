#ifndef TEXTCOMPONENT_H
#define TEXTCOMPONENT_H

#include "Component.h"
#include "Font.h"

namespace dae
{
	class TextureComponent;

	class TextComponent final : public Component
	{
	public:
		explicit TextComponent(GameObject* pOwner, std::string text = "", std::unique_ptr<Font> pFont = nullptr,
		                       const SDL_Color& color = {255, 255, 255, 255});
		explicit TextComponent(GameObject* pOwner, std::string text = "", std::string fontPath = "", int fontSize = 16,
		                       const SDL_Color& color = {255, 255, 255, 255});
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
		void SetColor(const SDL_Color& color);

	private:
		bool m_IsDirty{ true };
		std::string m_Text;
		SDL_Color m_Color;

		std::unique_ptr<Font> m_pFont;
		TextureComponent* m_pTextureComponent;
	};
}

#endif // TEXTCOMPONENT_H