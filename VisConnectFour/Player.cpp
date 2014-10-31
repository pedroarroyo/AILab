
#include "StdAfx.h"

#include "Player.h"
#include <vector>
#include "Game.h"

void PhysicalPlayer::DetermineMove(const Ai::ConnectFourMove& lastMove, Ai::ConnectFourGameBoardValue player, const Ai::ConnectFourGameBoard& gameBoard, unsigned& outRow, unsigned& outColumn)
{

	// TODO Dependency inject these streams in order to mock them for testing.
	Ai::ConnectFourGameBoardLocation loc;
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
			std::wcout << "Invalid Move - Try Again" << std::endl;
		}
	}
}

void AiPlayerRandom::DetermineMove(const Ai::ConnectFourMove& lastMove, Ai::ConnectFourGameBoardValue player, const Ai::ConnectFourGameBoard& gameBoard, unsigned& outRow, unsigned& outColumn)
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
			Ai::ConnectFourGameBoardLocation element = gameBoard.GetValue(row, column);
			if (element.m_contents == Ai::kConnectFourGameBoardValue_Empty)
			{
				outRow = row;
				outColumn = column;
				locationFound = true;
			}
		}
	}
	*/
}

