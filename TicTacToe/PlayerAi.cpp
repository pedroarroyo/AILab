#include "StdAfx.h"

#include "PlayerAi.h"

#include "ai/minimax.h"

void AiPlayerMiniMax::DetermineMove(const Ai::TicTacToeMove& lastMove, Ai::TicTacToePlayer player, const Ai::TicTacToeGameBoard& gameBoard, unsigned& outRow, unsigned& outColumn)
{
	// Constructs a new game tree.
	// TODO Add negation semantics to the tree player.
	Ai::TicTacToeTreeNode tree(lastMove, gameBoard);

	// Evalutes the next Move_t.
	int a = -std::numeric_limits<int>::max();
	int b = std::numeric_limits<int>::max();
	int depth = 10;

	Ai::TicTacToeMove bestMove;
	std::vector<Ai::TicTacToeMove> moves;
	tree.GenerateMoves(moves);
	for each(const Ai::TicTacToeMove& Move_t in moves)
	{
		// Generate a child for each Move_t.
		Ai::TicTacToePolicy game;
		Ai::TicTacToeTreeNode child = tree.GetChild(Move_t);
		int v = Ai::MiniMax<Ai::TicTacToeTreeNode, Ai::TicTacToePolicy>(child, 10, a, b, true, game);
		if (v > a) 
		{
			a = v;
			bestMove = Move_t;
		}
	}

	std::cerr << "Evaluated states: " << m_evaluatedStates << std::endl;
	outRow = bestMove.m_row;
	outColumn = bestMove.m_column;
}

