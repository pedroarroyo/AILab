#ifndef TICTACTOE_PLAYER_AI_H_
#define TICTACTOE_PLAYER_AI_H_

#include "Player.h"

#include "ai/examples/tic_tac_toe.h"

class AiPlayerMiniMax : public PlayerStrategy
{
public:
	AiPlayerMiniMax(Ai::TicTacToeGameBoardValue playerValue)
		: PlayerStrategy(kPlayerStrategyTypeAiDifficult)
		, m_searchDepth(3)
	{}

	// PlayerStrategy
	virtual void DetermineMove(const Ai::TicTacToeMove& lastMove, Ai::TicTacToeGameBoardValue player, const Ai::TicTacToeGameBoard& gameBoard, unsigned& outRow, unsigned& outColumn) override;

private:
	uint32_t m_searchDepth;
	uint32_t m_evaluatedStates;
};



#endif