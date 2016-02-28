#ifndef TICTACTOE_PLAYER_AI_H_
#define TICTACTOE_PLAYER_AI_H_

#include "Player.h"

#include "ai/examples/tictactoe.h"

class AiPlayerMiniMax : public PlayerStrategy
{
public:
	AiPlayerMiniMax(Ai::TicTacToePlayer playerValue)
		: PlayerStrategy(kPlayerStrategyTypeAiDifficult)
		, m_searchDepth(3)
	{}

	// PlayerStrategy
	virtual void DetermineMove(const Ai::TicTacToeMove& lastMove, Ai::TicTacToePlayer player, const Ai::TicTacToeGameBoard& gameBoard, unsigned& outRow, unsigned& outColumn) override;

private:
	uint32_t m_searchDepth;
	uint32_t m_evaluatedStates;
};



#endif