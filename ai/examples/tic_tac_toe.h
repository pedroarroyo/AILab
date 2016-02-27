#ifndef AI_TICTACTOE_H_
#define AI_TICTACTOE_H_

#include "GameBoard.h"
#include "Visitor.h"

namespace Ai
{
	// Types
	enum TicTacToePlayer
	{
		kTicTacToeGameBoardValue_Empty= 1,
		kTicTacToeGameBoardValue_O = 0,
		kTicTacToeGameBoardValue_X = -1
	};
	
	enum TicTacToeMoveResult
	{
		kMoveResultInvalid,
		kMoveResultNone,
		kMoveResultVictory,
		kMoveResultWinX,
		kMoveResultWinO,
		kMoveResultDraw,
	};

	typedef GameBoardLocation<TicTacToePlayer> TicTacToeGameBoardLocation;
	typedef GameBoard<TicTacToePlayer, 3, 3> TicTacToeGameBoard;

	// Forward declarations.
	class TicTacToeNode;
	class TicTacToeMove;

	// Helpers
	TicTacToeMoveResult AnalyzeMove(const TicTacToeGameBoard& gameBoard, const TicTacToeMove& Move_t);

	// Classes
	class TicTacToeMove : public Ai::GameTreeMove
	{
	public:
		TicTacToeMove() : m_row(0), m_column(0) {}
		TicTacToeMove(TicTacToePlayer value, unsigned row, unsigned column) 
			: m_value(value)
			, m_row(row)
			, m_column(column) {}

		TicTacToePlayer m_value;
		unsigned m_row;
		unsigned m_column;
	};

	class TicTacToeNode : public Ai::GameTreeNode< TicTacToeNode >
	{
	public:
		TicTacToeNode(const TicTacToeGameBoard& gameBoard) : m_gameBoard(gameBoard) {}
		int DetermineScore(bool returnMaximum) const
		{
			return 0;
		}

		void GenerateMoves(std::vector<TicTacToeMove>& moves) const
		{
			// Inverts the player when generating moves to our child nodes.
			TicTacToePlayer value = (m_move.m_value == kTicTacToeGameBoardValue_X) ? kTicTacToeGameBoardValue_O : kTicTacToeGameBoardValue_X;

			unsigned numRows = m_gameBoard.GetNumRows();
			unsigned numColumns = m_gameBoard.GetNumColumns();

			for (unsigned row = 0; row < numRows; row++)
			{
				for (unsigned column = 0; column < numColumns; column++)
				{
					GameBoardLocation<TicTacToePlayer> element = m_gameBoard.GetValue(row, column);
					if (element.m_contents == Ai::kTicTacToeGameBoardValue_Empty)
					{
						moves.emplace_back(value, row, column);
					}
				}
			}
		}

		TicTacToeNode GenerateChild( const TicTacToeMove& Move_t ) const
		{
			TicTacToeNode child(*this);
			child.m_gameBoard.SetValue(Move_t.m_row, Move_t.m_column, Move_t.m_value);
			return child;
		}

		bool IsTerminal() const
		{
			TicTacToeMoveResult result = AnalyzeMove(m_gameBoard, m_move);
			return (result == kMoveResultDraw || result == kMoveResultVictory);
		}

		TicTacToeNode GetChild(const TicTacToeMove& Move_t) const
		{
			TicTacToeNode child(m_gameBoard);
			child.m_gameBoard.SetValue(Move_t.m_row, Move_t.m_column, Move_t.m_value);
			return child;
		}

		/*
		generator begin() const
		{
			return generator(1);
		}

		generator end() const
		{
			return generator(m_maxn);
		}
*/
	private:
		TicTacToeGameBoard m_gameBoard;
		TicTacToeMove m_move;
		int m_maxn;
	};

	typedef GameTreeNodeVisitor<TicTacToeNode, TicTacToeMove> TicTacToeGameTreeNodeVisitor;


	/*
	template< class GameBoard >
	class TicTacToeGameTreeNodeVisitor : public GameTreeNodeVisitor< TicTacToeGameTreeNodeVisitor<GameBoard> >
	{
	public:
		TicTacToeGameTreeNodeVisitor(TicTacToeNode<GameBoard> node) : m_node(node) {}

		TicTacToeNode<GameBoard>& operator*() 
		{
			return m_node;
		}

		void GenerateMoves(std::vector<TicTacToeMove>& moves) const
		{
			m_node.GenerateMoves(moves);
		}

		bool IsTerminal() const
		{
			return m_node.IsTerminal();
		}

		int DetermineScore(bool returnMaximum) const
		{
			return m_node.DetermineScore(returnMaximum);
		}

	private:
		TicTacToeNode<GameBoard> m_node;
		TicTacToeMove m_move;

	};
	*/
}

#endif
