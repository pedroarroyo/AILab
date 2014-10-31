#include "stdafx.h"

#include "Vis/AsciiCanvas.h"

#include <iostream>

#include "Vis/AsciiSprite.h"

namespace Vis
{
	void AsciiCanvas::Clear()
	{

	}

	void AsciiCanvas::Draw(const Util::Vector2<unsigned>& upperLeft, const AsciiSprite& sprite)
	{
		// PLA_TODO Switch this to use memcopy.
		unsigned numColumns = sprite.GetWidth();
		unsigned numRows = sprite.GetHeight();
		for (unsigned row = 0; row < numRows && upperLeft.m_y + row < m_height; ++row)
		{
			for (unsigned column = 0; column < numColumns && upperLeft.m_x + column < m_width; ++column)
			{
				m_charArray.Set(upperLeft.m_x + column, upperLeft.m_y + row, sprite.GetValue(column, row));
			}
		}
	}

	std::wostream& operator<<(std::wostream& os, const AsciiCanvas& canvas)
	{
		for (unsigned row = 0; row < canvas.m_height; ++row)
		{
			for (unsigned column = 0; column < canvas.m_width; ++column)
			{
				os << canvas.m_charArray.At(column, row);
			}
			os << std::endl;
		}
		return os;
	}
}