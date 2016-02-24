// File: Game.h
// Author: Pedro Arroyo
// Description: 
// A "Game" class encapsulates all the policies relating to how the game is played
// (managing turns between players, determining victory conditions, game state queries, etc.).
// Usage:
// Once a game is initialized, turns can be simulated by iteratively calling NextTurn() until the game is complete.
// Note that a call to NextTurn() may be blocking due to waiting on user input.

#ifndef GAME_H_
#define GAME_H_

#include "AsciiSprite.h"
#include "Player.h"
#include "PlayerAi.h"
#include "ai/examples/tic_tac_toe.h"

class AsciiCanvas;

class Game
{
public:
	Game(unsigned boardSize, PlayerStrategyType playerX, PlayerStrategyType playerO);
	~Game();

	static const AsciiSprite kSpriteO;
	static const AsciiSprite kSpriteX;	
	static const AsciiSprite kSpriteGameBoard;	

	enum MoveResult
	{
		kMoveResultInvalid,
		kMoveResultNone,
		kMoveResultVictory,
		kMoveResultWinX,
		kMoveResultWinO,
		kMoveResultDraw,
	};
	Ai::TicTacToeMoveResult NextTurn();

	Ai::TicTacToeGameBoardValue GetCurrentPlayer() const { return m_currentPlayer; }

	void Draw( AsciiCanvas& canvas ) const;

protected:
	Ai::TicTacToeMoveResult ProcessTurn( Ai::TicTacToeGameBoardValue player, PlayerStrategy& strategy );

private:
	enum State
	{
		kStateProcessingPlayerX,
		kStateProcessingPlayerO,
		kStateGameOver
	};

	Ai::TicTacToeGameBoard m_gameBoard;

	PlayerStrategy* m_strategyPlayerX;
	PlayerStrategy* m_strategyPlayerO;

	Ai::TicTacToeMove m_lastMove;
	Ai::TicTacToeGameBoardValue m_currentPlayer;

//	AsciiSprite m_spriteBackground;
//	AsciiSprite m_spriteO;
//	AsciiSprite m_spriteX;

	State m_state;
};

#endif