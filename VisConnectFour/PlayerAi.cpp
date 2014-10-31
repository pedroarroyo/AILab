#include "StdAfx.h"

#include "PlayerAi.h"

#include "AI/Evaluator.h"

void AiPlayerMiniMax::DetermineMove(const Ai::ConnectFourMove& lastMove, Ai::ConnectFourGameBoardValue player, const Ai::ConnectFourGameBoard& gameBoard, unsigned& outRow, unsigned& outColumn)
{
	// Constructs a new game tree.
	// TODO Add negation semantics to the tree player.
	Ai::ConnectFourTreeNode tree(lastMove, gameBoard);

	// Evalutes the next move.
	int a = -std::numeric_limits<int>::max();
	int b = std::numeric_limits<int>::max();
	int depth = 10;

	Ai::ConnectFourMove bestMove;
	std::vector<Ai::ConnectFourMove> moves;
	tree.GenerateMoves(moves);
	for each(const Ai::ConnectFourMove& move in moves)
	{
		// Generate a child for each move.
		Ai::ConnectFourTreeNode child = tree.GetChild(move);
		int v = Ai::MiniMax(child, 10, a, b, true);
		if (v > a) 
		{
			a = v;
			bestMove = move;
		}
	}

	std::cerr << "Evaluated states: " << m_evaluatedStates << std::endl;
	outRow = bestMove.m_row;
	outColumn = bestMove.m_column;
}

