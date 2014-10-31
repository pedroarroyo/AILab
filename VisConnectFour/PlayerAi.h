#ifndef PLAYERAI_H_
#define PLAYERAI_H_

#include "Player.h"

#include "AI/Examples/ConnectFour.h"
#include <stdint.h>

class AiPlayerMiniMax : public PlayerStrategy
{
public:
	AiPlayerMiniMax(Ai::ConnectFourGameBoardValue playerValue)
		: PlayerStrategy(kPlayerStrategyTypeAiDifficult)
		, m_searchDepth(3)
	{}

	// PlayerStrategy
	virtual void DetermineMove(const Ai::ConnectFourMove& lastMove, Ai::ConnectFourGameBoardValue player, const Ai::ConnectFourGameBoard& gameBoard, unsigned& outRow, unsigned& outColumn) override;

private:
	uint32_t m_searchDepth;
	uint32_t m_evaluatedStates;
};



#endif