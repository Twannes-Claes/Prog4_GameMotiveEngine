#include <stdexcept>
#include <SDL_ttf.h>
#include "Font.h"

TTF_Font* Monke::Font::GetFont() const
{
	return m_font;
}

Monke::Font::Font(const std::string& fullPath, const unsigned int size) : m_font(nullptr), m_size(size)
{
	m_font = TTF_OpenFont(fullPath.c_str(),static_cast<int>(m_size));

	if (m_font == nullptr) 
	{
		throw std::runtime_error(std::string("Failed to load font: ") + SDL_GetError());
	}
}

Monke::Font::~Font()
{
	TTF_CloseFont(m_font);
}
