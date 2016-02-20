
#ifndef GAME_TREE_H_
#define GAME_TREE_H_

#include "GameBoard.h"

namespace MinMax
{
/*
	enum Player : bool
	{
		kPlayerMaximized = true,
		kPlayerMinimized = false
	};
*/
};
/*
class GameTreeNode
{
public:
	GameTreeNode( TicTacToe::PlayerDesignation player, const GameBoard& gameBoard, const GameBoard::Location& move ) : m_player( player), m_gameBoard( gameBoard ), m_move( move ) 
	{
	}
	int NumChildNodes() { return 8; }
	void GenerateChildNodes( std::vector<GameTreeNode>& ) const;
	bool IsTerminalNode() const;
	int DetermineScore(bool maximizingPlayer) const;

	TicTacToe::PlayerDesignation m_player;
	GameBoard m_gameBoard;
	GameBoard::Location m_move;
};

int MiniMax( const GameTreeNode& node, int depth, int a, int b, bool returnMaximum );
int NegaMax( const GameTreeNode& node, int depth, int a, int b, bool returnMaximum );
*/
#endif
