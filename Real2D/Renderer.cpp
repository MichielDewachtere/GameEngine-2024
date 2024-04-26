#include "Renderer.h"

#include <SDL_render.h>
#include <stdexcept>

#include "imgui_impl_sdl2.h"
#include "imgui_impl_sdlrenderer2.h"
#include "SceneManager.h"
#include "Texture2D.h"

int GetOpenGLDriverIndex()
{
	auto openglIndex = -1;
	const auto driverCount = SDL_GetNumRenderDrivers();
	for (auto i = 0; i < driverCount; i++)
	{
		SDL_RendererInfo info;
		if (!SDL_GetRenderDriverInfo(i, &info))
			if (!strcmp(info.name, "opengl"))
				openglIndex = i;
	}
	return openglIndex;
}

void real::Renderer::Init(SDL_Window* window)
{
	m_pWindow = window;
	m_pRenderer = SDL_CreateRenderer(window, GetOpenGLDriverIndex(), SDL_RENDERER_ACCELERATED);
	if (m_pRenderer == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateRenderer Error: ") + SDL_GetError());
	}
}

void real::Renderer::Render() const
{
#ifndef NDEBUG
	ImGui_ImplSDLRenderer2_NewFrame();
	ImGui_ImplSDL2_NewFrame();
	ImGui::NewFrame();
#endif

	const auto& color = GetBackgroundColor();
	SDL_SetRenderDrawColor(m_pRenderer, color.r, color.g, color.b, color.a);
	SDL_RenderClear(m_pRenderer);

	SceneManager::GetInstance().Render();

#ifndef NDEBUG
	SceneManager::GetInstance().OnGui();

	ImGui::Render();
	ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData());
#endif 
	SDL_RenderPresent(m_pRenderer);
}

void real::Renderer::Destroy()
{
	if (m_pRenderer != nullptr)
	{
		SDL_DestroyRenderer(m_pRenderer);
		m_pRenderer = nullptr;
	}
}

void real::Renderer::RenderTexture(const Texture2D& texture, const float x, const float y) const
{
	SDL_Rect dst{};
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	SDL_QueryTexture(texture.GetSDLTexture(), nullptr, nullptr, &dst.w, &dst.h);
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);
}

void real::Renderer::RenderTexture(const Texture2D& texture, const float x, const float y, const float width, const float height) const
{
	SDL_Rect dst;
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	dst.w = static_cast<int>(width);
	dst.h = static_cast<int>(height);
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);
}

void real::Renderer::RenderTexture(const Texture2D& texture, SDL_Rect rect) const
{
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &rect);
}

void real::Renderer::RenderSprite(const Texture2D& texture, glm::ivec4 src, glm::ivec4 dst, float angle,
	glm::ivec2 center, RenderFlip flip) const
{
	const SDL_Rect srcRect = GlmToSDLRect(src);
	const SDL_Rect dstRect = GlmToSDLRect(dst);

	RenderSpriteOrTexture(texture, &srcRect, dstRect, angle, center, flip);
}

SDL_Renderer* real::Renderer::GetSDLRenderer() const { return m_pRenderer; }

#pragma region geometry
void real::Renderer::RenderRectangle(const glm::ivec4& rect, bool isFilled, glm::u8vec4 color) const
{
	SDL_Color originalColor;
	SDL_GetRenderDrawColor(m_pRenderer, &originalColor.r, &originalColor.g, &originalColor.b, &originalColor.a);

	const SDL_Rect sdlRect{ rect.x, rect.y, rect.z, rect.w };

	SDL_SetRenderDrawColor(m_pRenderer, color.r, color.g, color.b, color.a);
	if (isFilled)
		SDL_RenderFillRect(GetSDLRenderer(), &sdlRect);
	else
		SDL_RenderDrawRect(GetSDLRenderer(), &sdlRect);
	SDL_SetRenderDrawColor(m_pRenderer, originalColor.r, originalColor.g, originalColor.b, originalColor.a);

}
void real::Renderer::RenderPoint(int x, int y, glm::u8vec4 color) const
{
	SDL_Color originalColor;
	SDL_GetRenderDrawColor(m_pRenderer, &originalColor.r, &originalColor.g, &originalColor.b, &originalColor.a);

	SDL_SetRenderDrawColor(m_pRenderer, color.r, color.g, color.b, color.a);
	SDL_RenderDrawPoint(GetSDLRenderer(), x, y);
	SDL_SetRenderDrawColor(m_pRenderer, originalColor.r, originalColor.g, originalColor.b, originalColor.a);
}
void real::Renderer::RenderLine(int x1, int y1, int x2, int y2, glm::u8vec4 color) const
{
	SDL_Color originalColor;
	SDL_GetRenderDrawColor(m_pRenderer, &originalColor.r, &originalColor.g, &originalColor.b, &originalColor.a);

	SDL_SetRenderDrawColor(m_pRenderer, color.r, color.g, color.b, 255);
	SDL_RenderDrawLine(GetSDLRenderer(), x1, y1, x2, y2);
	SDL_SetRenderDrawColor(m_pRenderer, originalColor.r, originalColor.g, originalColor.b, originalColor.a);
}
void real::Renderer::RenderShape(const glm::ivec2* points, int count, glm::u8vec4 color) const
{
	SDL_Color originalColor;
	SDL_GetRenderDrawColor(m_pRenderer, &originalColor.r, &originalColor.g, &originalColor.b, &originalColor.a);

	const auto sdlPoints = new SDL_Point[count];
	for (int i = 0; i < count; ++i)
		sdlPoints[i] = GlmToSDLPoint(points[i]);

	SDL_SetRenderDrawColor(m_pRenderer, color.r, color.g, color.b, 255);
	SDL_RenderDrawLines(m_pRenderer, sdlPoints, count);
	SDL_SetRenderDrawColor(m_pRenderer, originalColor.r, originalColor.g, originalColor.b, originalColor.a);

}
void real::Renderer::RenderShape(const std::vector<glm::ivec2>& points, glm::u8vec4 color) const
{
	RenderShape(&points.front(), static_cast<int>(points.size()), color);
}
#pragma endregion geometry
void real::Renderer::RenderSpriteOrTexture(const Texture2D& texture, const SDL_Rect* srcRect, const SDL_Rect& dstRect,
	float angle, glm::ivec2 center, RenderFlip flip) const
{
	const SDL_Point rotationCenter = GlmToSDLPoint(center);

	SDL_RendererFlip sdlFlip = SDL_FLIP_NONE;
	if (flip == RenderFlip::vertical) sdlFlip = SDL_FLIP_VERTICAL;
	else if (flip == RenderFlip::horizontal) sdlFlip = SDL_FLIP_HORIZONTAL;

	SDL_RenderCopyEx(GetSDLRenderer(), texture.GetSDLTexture(),
		srcRect, &dstRect, static_cast<double>(angle), &rotationCenter, sdlFlip);
}

SDL_Point real::Renderer::GlmToSDLPoint(const glm::ivec2& point)
{
	SDL_Point sdlPoint;
	sdlPoint.x = point.x;
	sdlPoint.y = point.y;
	return sdlPoint;
}

SDL_Rect real::Renderer::GlmToSDLRect(const glm::ivec4& rect)
{
	SDL_Rect sdlRect;
	sdlRect.x = rect.x;
	sdlRect.y = rect.y;
	sdlRect.w = rect.z;
	sdlRect.h = rect.w;
	return sdlRect;
}
