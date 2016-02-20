#ifndef AI_EXAMPLES_TICTACTOE_H_
#define AI_EXAMPLES_TICTACTOE_H_

#include "GameBoard.h"
#include "ai/node.h"

namespace Ai
{
	// Types
	enum TicTacToeGameBoardValue
	{
		kTicTacToeGameBoardValue_Empty= 1,
		kTicTacToeGameBoardValue_O = 0,
		kTicTacToeGameBoardValue_X = -1
	};
	
	enum TicTacToeMoveResult
	{
		kTicTacToeMoveResult_Invalid,
		kTicTacToeMoveResult_None,
		kTicTacToeMoveResult_Victory,
		kTicTacToeMoveResult_Draw
	};

	typedef GameBoardLocation<TicTacToeGameBoardValue> TicTacToeGameBoardLocation;
	typedef GameBoard<TicTacToeGameBoardValue, 3, 3> TicTacToeGameBoard_t;

	class TicTacToeGameBoard : public TicTacToeGameBoard_t
	{
	public: 
		TicTacToeGameBoard() : TicTacToeGameBoard_t(kTicTacToeGameBoardValue_Empty) {}
	};

	// Forward declarations.
	class TicTacToeNode;
	class TicTacToeMove;

	// Helpers
	TicTacToeMoveResult TicTacToeAnalyzeMove(const TicTacToeGameBoard& gameBoard, const TicTacToeMove& move);

	// Classes
	class TicTacToeMove : public Ai::Action
	{
	public:
		TicTacToeMove() : m_row(0), m_column(0) {}
		TicTacToeMove(TicTacToeGameBoardValue value, unsigned row, unsigned column) 
			: m_value(value)
			, m_row(row)
			, m_column(column) {}

		TicTacToeGameBoardValue m_value;
		unsigned m_row;
		unsigned m_column;
	};

	class TicTacToeTreeNode : public Ai::Node< TicTacToeNode >
	{
	public:
		// TODO - How do we handle passing in undefined board value?
		TicTacToeTreeNode(TicTacToeGameBoardValue initialPlayer, TicTacToeGameBoard gameBoard ) 
			: m_parentLink( (initialPlayer == kTicTacToeGameBoardValue_O) ?  kTicTacToeGameBoardValue_X : kTicTacToeGameBoardValue_O, 0, 0) 
			, m_gameBoard(gameBoard) {}

		TicTacToeTreeNode(TicTacToeMove move, TicTacToeGameBoard gameBoard)
			: m_parentLink(move)
			, m_gameBoard(gameBoard) {}

		int DetermineScore(bool returnMaximum) const
		{
			const TicTacToeMoveResult result = TicTacToeAnalyzeMove( m_gameBoard, m_parentLink );

			if (result == kTicTacToeMoveResult_Victory)
			{
				return returnMaximum ? 1 : -1;
			}

			return 0;
		}

		bool IsTerminal() const
		{
			TicTacToeMoveResult result = TicTacToeAnalyzeMove(m_gameBoard, m_parentLink);
			return (result == kTicTacToeMoveResult_Draw || result == kTicTacToeMoveResult_Victory);
		}

		void GenerateChildren(std::vector<TicTacToeTreeNode>& children) const
		{
			// Reverse the player from our parent link to generate the moves for the next ply.
			// TODO Create a new type that exposes not operator.
			TicTacToeGameBoardValue nextPlayer =
				m_parentLink.m_value == kTicTacToeGameBoardValue_O ? kTicTacToeGameBoardValue_X : kTicTacToeGameBoardValue_O;

			unsigned numRows = m_gameBoard.GetNumRows();
			unsigned numColumns = m_gameBoard.GetNumColumns();
			for (unsigned row = 0; row < numRows; row++)
			{
				for (unsigned column = 0; column < numColumns; column++)
				{
					GameBoardLocation<TicTacToeGameBoardValue> element = m_gameBoard.GetValue(row, column);
					if (element.m_contents == Ai::kTicTacToeGameBoardValue_Empty)
					{
						TicTacToeMove move(nextPlayer, row, column);
						TicTacToeGameBoard gameBoard(m_gameBoard);
						gameBoard.SetValue(row, column, nextPlayer);
						children.emplace_back(move, gameBoard);
					}
				}
			}
		}

		void GenerateMoves(std::vector<TicTacToeMove>& moves) const
		{
			// Reverse the player from our parent link to generate the moves for the next ply.
			// TODO Create a new type that exposes not operator.
			TicTacToeGameBoardValue playerValue =
				m_parentLink.m_value == kTicTacToeGameBoardValue_O ? kTicTacToeGameBoardValue_X : kTicTacToeGameBoardValue_O;

			unsigned numRows = m_gameBoard.GetNumRows();
			unsigned numColumns = m_gameBoard.GetNumColumns();
			for (unsigned row = 0; row < numRows; row++)
			{
				for (unsigned column = 0; column < numColumns; column++)
				{
					GameBoardLocation<TicTacToeGameBoardValue> element = m_gameBoard.GetValue(row, column);
					if (element.m_contents == Ai::kTicTacToeGameBoardValue_Empty)
					{
						moves.emplace_back(playerValue, row, column);
					}
				}
			}
		}

		TicTacToeTreeNode GenerateChild( const TicTacToeMove& move ) const
		{
			TicTacToeTreeNode child(*this);
			child.m_gameBoard.SetValue(move.m_row, move.m_column, move.m_value);
			return child;
		}

		TicTacToeTreeNode GetChild(const TicTacToeMove& move) const
		{
			TicTacToeTreeNode child(*this);
			child.m_gameBoard.SetValue(move.m_row, move.m_column, move.m_value);
			child.m_parentLink = move;
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
		TicTacToeMove m_parentLink;
		int m_maxn;
	};

	typedef Game<TicTacToeNode, TicTacToeMove> TicTacToeGameTreeNodeVisitor;


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
