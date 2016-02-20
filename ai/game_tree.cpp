
#include "stdafx.h"

#include "GameTree.h"

int MiniMax( const GameTreeNode& node, int depth, int a, int b, bool returnMaximum )
{
	if( depth == 0 || node.IsTerminalNode() )
	{
		//			++m_evaluatedStates;
		return node.DetermineScore(returnMaximum);
	}

	// Determines possible moves for this layer of the game tree.
	std::vector<GameTreeNode> childNodes;
	node.GenerateChildNodes( childNodes );
	if( returnMaximum ) 
	{
		for each (const GameTreeNode& childNode in childNodes) 
		{
			a = std::max(a, MiniMax(childNode, depth - 1, a, b, !returnMaximum));
			if (b <= a)
				return b; // beta cutoff.
		}
		return a;
	} 
	else 
	{
		for each (const GameTreeNode& childNode in childNodes) 
		{
			b = std::min(b, MiniMax(childNode, depth - 1, a, b, !returnMaximum));
			if (b <= a)
				return a; // alpha cutoff.
		}
		return b;
	}
}

int NegaMax( const GameTreeNode& node, int depth, int a, int b )
{
	if( depth == 0 || node.IsTerminalNode() )
	{
		//			++m_evaluatedStates;
//		return node.DetermineScore();
	}

	// Determines possible moves for this layer of the game tree.
	std::vector<GameTreeNode> childNodes;
	node.GenerateChildNodes( childNodes );
	for each (const GameTreeNode& childNode in childNodes) 
	{
		a = std::max(a, -NegaMax(childNode, depth - 1, -b, -a));
		if (b <= a)
			return b; // beta cutoff.
	}
	return a;
}

void GameTreeNode::GenerateChildNodes( std::vector<GameTreeNode>& childNodes ) const
{
	// Generates a list of all possible moves a player can make from the supplied gamestate.
	// TODO - Replace this with a generator/iterator that can calculate the moves on the fly.
	uint8_t boardSize = m_gameBoard.GetBoardSize();

	// Expand the vector as necessary.
	childNodes.reserve( boardSize * boardSize - m_gameBoard.GetNumOccupiedSquares() );

	TicTacToe::PlayerDesignation nextPlayer = (m_player == TicTacToe::kPlayerX) ? TicTacToe::kPlayerO : TicTacToe::kPlayerX;
	for( auto row = 0; row < boardSize; row++ )
	{
		for( auto column = 0; column < boardSize; column++ )
		{
			if( m_gameBoard.GetValue(row, column) == TicTacToe::kInvalidPlayer )
			{
				GameBoard::Location move(row, column);
				// PLA_TODO Known bug in VS2010. Change this to an emplace to avoid creation of a temporary after moving project to VC2012 or later.
				GameTreeNode newNode(nextPlayer, m_gameBoard, move);
				newNode.m_gameBoard.SetValue(move.m_row,move.m_column, nextPlayer);
				childNodes.push_back(newNode);
//				childNodes.emplace_back(nextPlayer, m_gameBoard, move);
			}
		}
	}
}

bool GameTreeNode::IsTerminalNode() const
{
	Game::MoveResult moveResult = Game::AnalyzeMove( m_player, m_gameBoard, m_move.m_row, m_move.m_column );
	return ( moveResult == Game::kMoveResultVictory ) || ( moveResult == Game::kMoveResultDraw );
}


int GameTreeNode::DetermineScore(bool maximizingPlayer) const
{
	const Game::MoveResult result = Game::AnalyzeMove( m_player, m_gameBoard, m_move.m_row, m_move.m_column );

	if( result == Game::kMoveResultVictory )
	{
		return maximizingPlayer ? -1 : 1;
	}

	return 0;
}
