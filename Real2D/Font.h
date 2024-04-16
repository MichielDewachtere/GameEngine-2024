#ifndef FONT_H
#define FONT_H

#include <memory>
#include <string>
#include <glm/vec4.hpp>

#include "Texture2D.h"

struct _TTF_Font;
namespace real
{
	/**
	 * Simple RAII wrapper for a _TTF_Font
	 */
	class Font final
	{
	public:
		explicit Font(const std::string& fullPath, unsigned int size);
		~Font();

		Font(const Font &) = delete;
		Font & operator= (const Font &) = delete;
		Font(Font &&) = delete;
		Font & operator= (const Font &&) = delete;

		_TTF_Font* GetFont() const;

		std::unique_ptr<Texture2D> CreateTexture(const std::string& text, glm::u8vec4 color) const;

	private:
		_TTF_Font* m_pFont;
	};
}

#endif // FONT_H