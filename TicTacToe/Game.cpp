#include "StdAfx.h"

#include "Game.h"

//#include "curses.h"
#include <assert.h>
#include "AsciiCanvas.h"
#include "GameBoard.h"
#include "Player.h"

static const wchar_t kSpriteDataX[] = {
' ', ' ', ' ', ' ', ' ', ' ',
' ', '\\', ' ', ' ', '/', ' ',
' ', ' ', '>', '<', ' ', ' ',
' ', '/', ' ', ' ', '\\', ' ',
' ', ' ', ' ', ' ', ' ', ' '};
const AsciiSprite Game::kSpriteX( kSpriteDataX, 6, 5 );

static const wchar_t kSpriteDataO[] = { 
' ', ' ', ' ', ' ', ' ', ' ',
' ', ' ', '-', '-', ' ', ' ',
' ', '|', ' ', ' ', '|', ' ',
' ', ' ', '-', '-', ' ', ' ',
' ', ' ', ' ', ' ', ' ', ' '};
const AsciiSprite Game::kSpriteO( kSpriteDataO, 6, 5 );

static const wchar_t kSpriteDataGameBoard[] = { 
	' ', ' ', ' ', ' ', ' ', ' ', L'\u2588', ' ', ' ', ' ', ' ', ' ', ' ', L'\u2588', ' ', ' ', ' ', ' ', ' ', ' ',
	' ', ' ', ' ', ' ', ' ', ' ', L'\u2588', ' ', ' ', ' ', ' ', ' ', ' ', L'\u2588', ' ', ' ', ' ', ' ', ' ', ' ',
	' ', ' ', ' ', ' ', ' ', ' ', L'\u2588', ' ', ' ', ' ', ' ', ' ', ' ', L'\u2588', ' ', ' ', ' ', ' ', ' ', ' ',
	' ', ' ', ' ', ' ', ' ', ' ', L'\u2588', ' ', ' ', ' ', ' ', ' ', ' ', L'\u2588', ' ', ' ', ' ', ' ', ' ', ' ',
	' ',      ' ',      ' ',      ' ',      ' ',      ' ',      L'\u2588', ' ',      ' ',      ' ',      ' ',      ' ', ' ', L'\u2588', ' ', ' ', ' ', ' ', ' ', ' ',
	L'\u2588', L'\u2588', L'\u2588', L'\u2588', L'\u2588', L'\u2588', L'\u2588', L'\u2588', L'\u2588', L'\u2588', L'\u2588', L'\u2588', L'\u2588', L'\u2588', L'\u2588', L'\u2588', L'\u2588', L'\u2588', L'\u2588', L'\u2588',
	' ', ' ', ' ', ' ', ' ', ' ', L'\u2588', ' ', ' ', ' ', ' ', ' ', ' ', L'\u2588', ' ', ' ', ' ', ' ', ' ', ' ',
	' ', ' ', ' ', ' ', ' ', ' ', L'\u2588', ' ', ' ', ' ', ' ', ' ', ' ', L'\u2588', ' ', ' ', ' ', ' ', ' ', ' ',
	' ', ' ', ' ', ' ', ' ', ' ', L'\u2588', ' ', ' ', ' ', ' ', ' ', ' ', L'\u2588', ' ', ' ', ' ', ' ', ' ', ' ',
	' ', ' ', ' ', ' ', ' ', ' ', L'\u2588', ' ', ' ', ' ', ' ', ' ', ' ', L'\u2588', ' ', ' ', ' ', ' ', ' ', ' ',
	' ', ' ', ' ', ' ', ' ', ' ', L'\u2588', ' ', ' ', ' ', ' ', ' ', ' ', L'\u2588', ' ', ' ', ' ', ' ', ' ', ' ',
	L'\u2588', L'\u2588', L'\u2588', L'\u2588', L'\u2588', L'\u2588', L'\u2588', L'\u2588', L'\u2588', L'\u2588', L'\u2588', L'\u2588', L'\u2588', L'\u2588', L'\u2588', L'\u2588', L'\u2588', L'\u2588', L'\u2588', L'\u2588',
	' ', ' ', ' ', ' ', ' ', ' ', L'\u2588', ' ', ' ', ' ', ' ', ' ', ' ', L'\u2588', ' ', ' ', ' ', ' ', ' ', ' ',
	' ', ' ', ' ', ' ', ' ', ' ', L'\u2588', ' ', ' ', ' ', ' ', ' ', ' ', L'\u2588', ' ', ' ', ' ', ' ', ' ', ' ',
	' ', ' ', ' ', ' ', ' ', ' ', L'\u2588', ' ', ' ', ' ', ' ', ' ', ' ', L'\u2588', ' ', ' ', ' ', ' ', ' ', ' ',
	' ', ' ', ' ', ' ', ' ', ' ', L'\u2588', ' ', ' ', ' ', ' ', ' ', ' ', L'\u2588', ' ', ' ', ' ', ' ', ' ', ' ',
	' ', ' ', ' ', ' ', ' ', ' ', L'\u2588', ' ', ' ', ' ', ' ', ' ', ' ', L'\u2588', ' ', ' ', ' ', ' ', ' ', ' '};

const AsciiSprite Game::kSpriteGameBoard( kSpriteDataGameBoard, 20, 17 );


namespace
{
	// TODO Implement this as a proper factory.
	PlayerStrategy* CreatePlayerStrategy( Ai::TicTacToePlayer playerValue, PlayerStrategyType strategyType )
	{
		PlayerStrategy* playerStrategy = nullptr;
		switch(strategyType)
		{
		case kPlayerStrategyTypeHuman:
			playerStrategy = new PhysicalPlayer();
			break;
		case kPlayerStrategyTypeAiEasy:
			playerStrategy = new AiPlayerRandom();
			break;
		case kPlayerStrategyTypeAiDifficult:
			playerStrategy = new AiPlayerMiniMax(playerValue);
			break;
		default:
			assert(0); // Unimplemented strategy
			break;
		}

		return playerStrategy;
	}
}

Game::Game( unsigned boardSize, PlayerStrategyType playerX, PlayerStrategyType playerO )
	: m_currentPlayer( Ai::kTicTacToeGameBoardValue_X )
	, m_state( kStateProcessingPlayerX )
{
	m_strategyPlayerO = CreatePlayerStrategy(Ai::kTicTacToeGameBoardValue_O, playerO);
	m_strategyPlayerX = CreatePlayerStrategy(Ai::kTicTacToeGameBoardValue_X, playerX);
}

Game::~Game()
{
	delete m_strategyPlayerO;
	delete m_strategyPlayerX;
}

Ai::TicTacToeMoveResult Game::NextTurn()
{
	// Determines current player.
	TicTacToe::PlayerDesignation currentDesignation = TicTacToe::kInvalidPlayer;
	PlayerStrategy* currentStrategy = nullptr;

	Ai::TicTacToeMoveResult result = Ai::kTicTacToeMoveResult_Invalid;
	switch( m_state )
	{
	case kStateProcessingPlayerX:
		{
			m_currentPlayer = Ai::kTicTacToeGameBoardValue_X;
			result = ProcessTurn(Ai::kTicTacToeGameBoardValue_X, *m_strategyPlayerX);
			if( result == kMoveResultVictory || result == kMoveResultDraw )
			{
				m_state = kStateGameOver;
			}
			else
			{
				m_state = kStateProcessingPlayerO;
			}
			break;
		}

	case kStateProcessingPlayerO:
		{
			m_currentPlayer = Ai::kTicTacToeGameBoardValue_O;
			result = ProcessTurn(Ai::kTicTacToeGameBoardValue_O, *m_strategyPlayerO);
			if( result == kMoveResultVictory || result == kMoveResultDraw )
			{
				m_state = kStateGameOver;
			}
			else
			{
				m_state = kStateProcessingPlayerX;
			}
			break;
		}
	case kStateGameOver:
	default:
		break;
	}

	return result;
}

Ai::TicTacToeMoveResult Game::ProcessTurn( Ai::TicTacToePlayer player, PlayerStrategy& strategy )
{
	// Determines current player Move_t.
	unsigned row = 0, column = 0;
	strategy.DetermineMove( m_lastMove, player, m_gameBoard, row, column );
	m_lastMove.m_value = player;
	m_lastMove.m_row = row;
	m_lastMove.m_column = column;

	bool isValid = m_gameBoard.SetValue(row, column, player);
	if(!isValid)
	{
		return Ai::kTicTacToeMoveResult_Invalid;
	}
	else
	{
		return Ai::TicTacToeAnalyzeMove(m_gameBoard, m_lastMove);
	}	
}

void Game::Draw(AsciiCanvas& canvas) const
{
	
//	initscr();                    /* Start curses mode */
//	printw("Hello World !!!");    /* Print Hello World */
//	refresh();                    /* Print it on to the real screen */
//	getch();                      /* Wait for user input */
//	endwin();                     /* End curses mode */

	// Renders game board state to canvas
	canvas.Draw( Util::Vector2<unsigned>(0,0), kSpriteGameBoard );

	// Overlays the game pieces
	unsigned boardSize = m_gameBoard.GetNumColumns();
	
	unsigned spriteX = 0;
	unsigned spriteY = 0;

	for( unsigned row = 0; row < boardSize; row++ )
	{
		spriteX = 0;
		for( unsigned column = 0; column < boardSize; column++ )
		{
			Ai::TicTacToeGameBoardLocation location = m_gameBoard.GetValue(row, column);
			Ai::TicTacToePlayer value = location.m_contents;
			if(  value == Ai::kTicTacToeGameBoardValue_X )
			{
				canvas.Draw( Util::Vector2<unsigned>( spriteX, spriteY ), kSpriteX );
			}
			else if( value == Ai::kTicTacToeGameBoardValue_O )
			{
				canvas.Draw( Util::Vector2<unsigned>( spriteX, spriteY ), kSpriteO );
			}

			spriteX += 7; 
		}

		spriteY += 6; 
	}
}
