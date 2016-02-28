#include "StdAfx.h"

#include "ai/examples/tictactoe.h"

namespace Ai
{
	TicTacToeMoveResult TicTacToeAnalyzeMove(const TicTacToeGameBoard& gameBoard, const TicTacToeMove& move)
	{
		// Checks victory conditions.
		int boardSize = gameBoard.GetNumRows();
		int column = move.m_column;
		int row = move.m_row;
		int player = move.m_value;

		// Checks column
		for (int testRow = 0; testRow < boardSize; testRow++)
		{
			if (gameBoard.GetValue(testRow, column).m_contents != player)
			{
				break;
			}
			if (testRow == boardSize - 1)
			{
				return kTicTacToeMoveResult_Victory;
			}
		}

		// Checks row
		for (int testColumn = 0; testColumn < boardSize; testColumn++)
		{
			if (gameBoard.GetValue(row, testColumn).m_contents != player)
			{
				break;
			}
			if (testColumn == boardSize - 1)
			{
				return kTicTacToeMoveResult_Victory;
			}
		}

		// Checks diagonal
		if (row == column)
		{
			for (int i = 0; i < boardSize; i++)
			{
				if (gameBoard.GetValue(i, i).m_contents != player)
				{
					break;
				}
				if (i == boardSize - 1)
				{
					return kTicTacToeMoveResult_Victory;
				}
			}
		}

		// Checks anti-diagonal
		if ((row + column) == (boardSize - 1))
		{
			for (int i = 0; i < boardSize; i++)
			{
				if (gameBoard.GetValue(i, boardSize - 1 - i).m_contents != player)
				{
					break;
				}
				if (i == boardSize - 1)
				{
					return kTicTacToeMoveResult_Victory;
				}
			}
		}

		// Checks draw
		if (gameBoard.GetNumOccupiedLocations() == (boardSize * boardSize))
		{
			return kTicTacToeMoveResult_Draw;
		}

		return kTicTacToeMoveResult_None;
	}
}
