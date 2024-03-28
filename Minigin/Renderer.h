#ifndef RENDER_H
#define RENDER_H

#include <SDL_render.h>
#include <SDL_video.h>
#include <vector>
#include <glm/vec2.hpp>
#include <glm/vec4.hpp>

#include "Singleton.h"

namespace dae
{
	class Texture2D;

	enum class RenderFlip : char
	{
		none = 0,
		vertical = 1,
		horizontal = 2
	};

	class Renderer final : public Singleton<Renderer>
	{
	public:
		void Init(SDL_Window* window);
		void Render() const;
		void Destroy();

		void RenderTexture(const Texture2D& texture, float x, float y) const;
		void RenderTexture(const Texture2D& texture, float x, float y, float width, float height) const;
		void RenderTexture(const Texture2D& texture, SDL_Rect rect) const;

		void RenderSprite(const Texture2D& texture, glm::ivec4 src, glm::ivec4 dst, float angle = 0,
			glm::ivec2 center = { 0, 0 }, RenderFlip flip = RenderFlip::none) const;

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

		void RenderSpriteOrTexture(const Texture2D& texture, const SDL_Rect* srcRect, const SDL_Rect& dstRect,
			float angle, glm::ivec2 center, RenderFlip flip) const;

		static SDL_Point GlmToSDLPoint(const glm::ivec2& point);
		static SDL_Rect GlmToSDLRect(const glm::ivec4& rect);
	};
}

#endif // RENDER_H