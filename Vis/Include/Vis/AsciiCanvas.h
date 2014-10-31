#ifndef VIS_ASCII_CANVAS_H
#define VIS_ASCII_CANVAS_H


#include <iostream>
#include "Vis/Math.h"

namespace Vis
{
	class AsciiSprite;

	class AsciiCanvas
	{
	public:
		AsciiCanvas(unsigned width, unsigned height)
			: m_charArray(' ', width, height)
			, m_height(height)
			, m_width(width)
		{
		}
		~AsciiCanvas() {}

		uint32_t GetWidth() const { return m_width; }
		uint32_t GetHeight() const { return m_height; }

		void Clear();
		void Draw(const Util::Vector2<unsigned>& upperLeft, const AsciiSprite& sprite);

		friend std::wostream& operator<<(std::wostream& os, const AsciiCanvas& dt);

	private:
		Util::Array2D<wchar_t> m_charArray;

		uint32_t m_height;
		uint32_t m_width;
	};
}

#endif