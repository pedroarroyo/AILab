
#include <iostream>
#include <io.h>
#include <fcntl.h>
#include <windows.h>

#include "AsciiCanvas.h"
#include "Game.h"

namespace
{
	unsigned int g_boardSize = 3;

	void ClearConsole()
	{
		system("cls");

		COORD pos = {0, 0};
		HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);    
		SetConsoleCursorPosition(handle, pos);
	};

	void HandleGameResult( Ai::TicTacToeGameBoardValue player, Ai::TicTacToeMoveResult MoveResult )
	{
		if( MoveResult == Game::kMoveResultDraw )
		{
			std::wcout << "Game is a DRAW...";
		}
		else
		{
			switch( player )
			{
			case TicTacToe::kPlayerO:
				std::wcout << "Player 'O' WINS!" << std::endl;
				break;
			case TicTacToe::kPlayerX:
				std::wcout << "Player 'X' WINS!" << std::endl;
			}
		}

		std::wcout << "Press ENTER to quit." << std::endl;	
		char dummy = '\0';
		fflush(stdin);
		while( fread((void*)&dummy, 1, 1, stdin) == 0 )
		{
			// Block until player presses key.
		}
	}
}

int main()
{
	_setmode(_fileno(stdout), _O_U16TEXT);

	// Sets up resources.
	AsciiCanvas canvas(30, 20);
	Game game( g_boardSize, kPlayerStrategyTypeHuman, kPlayerStrategyTypeAiDifficult );

	// Simulates the game.
    unsigned row = 0, column = 0;
	Ai::TicTacToeMoveResult moveResult = Ai::kTicTacToeMoveResult_None;
    for( ; moveResult != Ai::kTicTacToeMoveResult_Victory && moveResult != Ai::kTicTacToeMoveResult_Draw; moveResult = game.NextTurn() )
    {
		ClearConsole();
		game.Draw(canvas);
		std::wcout << canvas;
    }

	ClearConsole();
	game.Draw(canvas);
	std::wcout << canvas;

	HandleGameResult( game.GetCurrentPlayer(), moveResult);

	return 0;
}