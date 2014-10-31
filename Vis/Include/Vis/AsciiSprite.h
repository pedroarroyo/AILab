#ifndef VIS_ASCII_SPRITE_H
#define VIS_ASCII_SPRITE_H

#include "Math.h"

namespace Vis
{
	class AsciiSprite
	{
	public:
		AsciiSprite(const char arr[], unsigned width, unsigned height)
			: m_charArray(arr, width, height)
			, m_height(height)
			, m_width(width) {}

		unsigned GetHeight() const { return m_height; }
		unsigned GetWidth() const { return m_width; }

		// PLA Replace this access with fast memcopy
		char GetValue(unsigned x, unsigned y) const { return m_charArray.At(x, y); }

	private:
		Util::Array2D<char> m_charArray;

		unsigned m_height;
		unsigned m_width;
	};
}

#endif