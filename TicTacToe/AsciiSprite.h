#ifndef TETRIS_ASCII_SPRITE_H
#define TETRIS_ASCII_SPRITE_H

#include "GameMath.h"

class AsciiSprite
{
public:
	AsciiSprite(const wchar_t arr[], unsigned width, unsigned height)
		: m_charArray(arr, width, height)
		, m_height(height)
		, m_width(width) {}

	unsigned GetHeight() const { return m_height; }
	unsigned GetWidth() const { return m_width; }

	// PLA Replace this access with fast memcopy
	wchar_t GetValue(unsigned x, unsigned y) const { return m_charArray.At(x, y); } 

private:
	Util::Array2D<wchar_t> m_charArray;

	unsigned m_height;
	unsigned m_width;
};

#endif