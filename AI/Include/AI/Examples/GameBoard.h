
#ifndef AI_GAMEBOARD_H_
#define AI_GAMEBOARD_H_

#include <array>

namespace Ai
{
	// Types
	enum GameBoardSetResult
	{

	};

	template< typename ValueType >
	struct GameBoardLocation
	{
		GameBoardLocation() : m_isNull(true) {}
		GameBoardLocation(ValueType value) : m_isNull(false), m_contents(value) {}
		bool m_isNull;
		ValueType m_contents;
	};

	template< typename GameBoardValue, unsigned NumRows = 0, unsigned NumColumns = 0 >
	class GameBoard
	{
	public:
		GameBoard(GameBoardValue emptyValue)
			: m_numColumns(NumColumns)
			, m_numRows(NumRows)
			, m_numOccupiedLocations(0)
			, m_nullElement( emptyValue )
		{
			m_values.fill(GameBoardLocation<GameBoardValue>(emptyValue));
		}

		unsigned GetNumOccupiedLocations() const
		{
			return m_numOccupiedLocations;
		}

		unsigned GetNumRows() const
		{
			return m_numRows;
		}

		unsigned GetNumColumns() const
		{
			return m_numColumns;
		}

		GameBoardLocation<GameBoardValue> GetValue( unsigned row, unsigned column) const
		{
			if ( row >= m_numRows || column >= m_numColumns )
			{
				return GameBoardLocation<GameBoardValue>();
			}

			return m_values[column + m_numColumns * row];
		}

		bool SetValue( unsigned row, unsigned column, GameBoardValue value )
		{
			if (row >= m_numRows || column >= m_numColumns) return false;

			if (m_values[column + m_numColumns * row].m_contents != value)
			{
				m_values[column + m_numColumns * row].m_contents = value;
				if (value != m_nullElement)
				{
					m_numOccupiedLocations++;
				}
			}

			return true;
		}
	private:
		GameBoardValue m_nullElement;

		unsigned m_numColumns;
		unsigned m_numRows;
		unsigned m_numOccupiedLocations;

		// TODO Optimize this for memory.
		std::array<GameBoardLocation<GameBoardValue>, NumRows * NumColumns> m_values;
	};
}

#endif
