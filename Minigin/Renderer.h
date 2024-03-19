#ifndef RENDER_H
#define RENDER_H

#include "Singleton.h"

namespace dae
{
	class Texture2D;
	/**
	 * Simple RAII wrapper for the SDL renderer
	 */
	class Renderer final : public Singleton<Renderer>
	{
	public:
		void Init(SDL_Window* window);
		void Render() const;
		void Destroy();

		void RenderTexture(const Texture2D& texture, float x, float y) const;
		void RenderTexture(const Texture2D& texture, float x, float y, float width, float height) const;
		void RenderTexture(const Texture2D& texture, SDL_Rect rect) const;

		SDL_Renderer* GetSDLRenderer() const;

		const SDL_Color& GetBackgroundColor() const { return m_ClearColor; }
		void SetBackgroundColor(const SDL_Color& color) { m_ClearColor = color; }

		void RenderRectangle(const glm::ivec4& rect, bool isFilled, glm::u8vec4 color) const;
		void RenderPoint(int x, int y, glm::u8vec4 color) const;
		void RenderLine(int x1, int y1, int x2, int y2, glm::u8vec4 color) const;
		void RenderShape(const glm::ivec2* points, int count, glm::u8vec4 color) const;
		void RenderShape(const std::vector<glm::ivec2>& points, glm::u8vec4 color) const;

	private:
		SDL_Renderer* m_pRenderer{};
		SDL_Window* m_pWindow{};
		SDL_Color m_ClearColor{};

		static SDL_Point GlmToSDLPoint(const glm::ivec2& point);
	};
}

#endif // RENDER_H