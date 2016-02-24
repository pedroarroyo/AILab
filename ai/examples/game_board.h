
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
		{
			m_values.fill(GameBoardLocation<GameBoardValue>(emptyValue));
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
//				if (value != m_unoccupiedValue)
//				{
//					m_numOccupiedLocations++;
//				}
			}

			return true;
		}
		/*
		void GenerateChildNodes( const std::vector< GameBoard<ValueType, NumRows, NumColumns> >& children ) 
		{
			// Generates a list of all possible moves a player can make from the supplied gamestate.
			// TODO - Replace this with a generator/iterator that can calculate the moves on the fly.
			uint8_t boardSize = m_numColumns * m_numRows;

			// Expand the vector as necessary.
			childNodes.reserve(boardSize * boardSize - m_gameBoard.GetNumOccupiedSquares());

			TicTacToe::PlayerDesignation nextPlayer = (m_player == TicTacToe::kPlayerX) ? TicTacToe::kPlayerO : TicTacToe::kPlayerX;
			for (auto row = 0; row < boardSize; row++)
			{
				for (auto column = 0; column < boardSize; column++)
				{
					if (m_gameBoard.GetValue(row, column) == TicTacToe::kInvalidPlayer)
					{
						GameBoard::Location move(row, column);
						// PLA_TODO Known bug in VS2010. Change this to an emplace to avoid creation of a temporary after moving project to VC2012 or later.
						GameTreeNode newNode(nextPlayer, m_gameBoard, move);
						newNode.m_gameBoard.SetValue(move.m_row, move.m_column, nextPlayer);
						childNodes.push_back(newNode);
						//				childNodes.emplace_back(nextPlayer, m_gameBoard, move);
					}
				}
			}
		}

		void DetermineScore(bool returnMaximum)
		{
			const MoveResult result = AnalyzeMove(m_player, m_gameBoard, m_move.m_row, m_move.m_column);

			if (result == kMoveResultVictory)
			{
				return maximizingPlayer ? -1 : 1;
			}

			return 0;
		}
		*/
	private:
		static GameBoardValue m_nullElement;

		unsigned m_numColumns;
		unsigned m_numRows;
		unsigned m_numOccupiedLocations;

		// TODO Optimize this for memory.
		std::array<GameBoardLocation<GameBoardValue>, NumRows * NumColumns> m_values;
	};
}

#endif
