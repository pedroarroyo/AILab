
#include "StdAfx.h"

#include "Player.h"
#include <vector>
#include "Game.h"

void PhysicalPlayer::DetermineMove(const Ai::TicTacToeMove& lastMove, Ai::TicTacToePlayer player, const Ai::TicTacToeGameBoard& gameBoard, unsigned& outRow, unsigned& outColumn)
{

	// TODO Dependency inject these streams in order to mock them for testing.
	Ai::TicTacToeGameBoardLocation loc;
	while( loc.m_isNull )
	{
		std::wcout << L"Player \U00000444" << static_cast<char>(player) << " input [row] [column]: ";
		std::cin.sync();
		std::cin >> outRow >> outColumn;

		if(std::cin.fail())
		{
			std::cin.clear();
			std::cin.ignore();
		}

		loc = gameBoard.GetValue(outRow, outColumn);
		if( loc.m_isNull ) 
		{
			std::wcout << "Invalid Move_t - Try Again" << std::endl;
		}
	}
}

void AiPlayerRandom::DetermineMove(const Ai::TicTacToeMove& lastMove, Ai::TicTacToePlayer player, const Ai::TicTacToeGameBoard& gameBoard, unsigned& outRow, unsigned& outColumn)
{
	/*
	// Selects the first unoccupied square starting from the upper right.
	unsigned numRows = gameBoard.GetNumRows();
	unsigned numColumns = gameBoard.GetNumColumns();

	bool locationFound = false;
	for( unsigned row = 0; row < numRows && !locationFound; row++ )
	{
		for( unsigned column = 0; column < numColumns && !locationFound; column++ )
		{
			Ai::TicTacToeGameBoardLocation element = gameBoard.GetValue(row, column);
			if (element.m_contents == Ai::kTicTacToeGameBoardValue_Empty)
			{
				outRow = row;
				outColumn = column;
				locationFound = true;
			}
		}
	}
	*/
}

