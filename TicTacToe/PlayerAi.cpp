#include "StdAfx.h"

#include "PlayerAi.h"

#include "AI/Evaluator.h"

void AiPlayerMiniMax::DetermineMove(const Ai::TicTacToeMove& lastMove, Ai::TicTacToeGameBoardValue player, const Ai::TicTacToeGameBoard& gameBoard, unsigned& outRow, unsigned& outColumn)
{
	// Constructs a new game tree.
	// TODO Add negation semantics to the tree player.
	Ai::TicTacToeTreeNode tree(lastMove, gameBoard);

	// Evalutes the next move.
	int a = -std::numeric_limits<int>::max();
	int b = std::numeric_limits<int>::max();
	int depth = 10;

	Ai::TicTacToeMove bestMove;
	std::vector<Ai::TicTacToeMove> moves;
	tree.GenerateMoves(moves);
	for each(const Ai::TicTacToeMove& move in moves)
	{
		// Generate a child for each move.
		Ai::TicTacToeTreeNode child = tree.GetChild(move);
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

