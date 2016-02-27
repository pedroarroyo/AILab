#ifndef AI_EXAMPLES_CONNECTFOUR_H_
#define AI_EXAMPLES_CONNECTFOUR_H_

#include "GameBoard.h"
#include "ai/node.h"

namespace Ai
{
	// Types
	enum ConnectFourGameBoardValue
	{
		kConnectFourGameBoardValue_Empty = 1,
		kConnectFourGameBoardValue_Red = 0,
		kConnectFourGameBoardValue_Black = -1
	};

	enum ConnectFourMoveResult
	{
		kConnectFourMoveResult_Invalid,
		kConnectFourMoveResult_None,
		kConnectFourMoveResult_Victory,
		kConnectFourMoveResult_Draw
	};

	typedef GameBoardLocation<ConnectFourGameBoardValue> ConnectFourGameBoardLocation;
	typedef GameBoard<ConnectFourGameBoardValue, 6, 7> ConnectFourGameBoard_t;

	class ConnectFourGameBoard : public ConnectFourGameBoard_t
	{
	public:
		ConnectFourGameBoard() : ConnectFourGameBoard_t(kConnectFourGameBoardValue_Empty) {}
	};

	// Forward declarations.
	class ConnectFourNode;
	class ConnectFourMove;

	// Helpers
	ConnectFourMoveResult ConnectFourAnalyzeMove(const ConnectFourGameBoard& gameBoard, const ConnectFourMove& Move_t);

	// Classes
	class ConnectFourMove : public Action
	{
	public:
		ConnectFourMove() : m_row(0), m_column(0) {}
		ConnectFourMove(ConnectFourGameBoardValue value, unsigned row, unsigned column)
			: m_value(value)
			, m_row(row)
			, m_column(column) {}

		ConnectFourGameBoardValue m_value;
		unsigned m_row;
		unsigned m_column;
	};

	class ConnectFourTreeNode : public Ai::Node< ConnectFourNode >
	{
	public:
		// TODO - How do we handle passing in undefined board value?
		ConnectFourTreeNode(ConnectFourGameBoardValue initialPlayer, ConnectFourGameBoard gameBoard)
			: m_parentLink((initialPlayer == kConnectFourGameBoardValue_Red) ? kConnectFourGameBoardValue_Black : kConnectFourGameBoardValue_Red, 0, 0)
			, m_gameBoard(gameBoard) {}

		ConnectFourTreeNode(ConnectFourMove Move_t, ConnectFourGameBoard gameBoard)
			: m_parentLink(Move_t)
			, m_gameBoard(gameBoard) {}

		int DetermineScore(bool returnMaximum) const
		{
			const ConnectFourMoveResult result = ConnectFourAnalyzeMove(m_gameBoard, m_parentLink);

			if (result == kConnectFourMoveResult_Victory)
			{
				return returnMaximum ? 1 : -1;
			}

			return 0;
		}

		bool IsTerminal() const
		{
			ConnectFourMoveResult result = ConnectFourAnalyzeMove(m_gameBoard, m_parentLink);
			return (result == kConnectFourMoveResult_Draw || result == kConnectFourMoveResult_Victory);
		}

		void GenerateChildren(std::vector<ConnectFourTreeNode>& children) const
		{
			// Reverse the player from our parent link to generate the moves for the next ply.
			// TODO Create a new type that exposes not operator.
			ConnectFourGameBoardValue nextPlayer =
				m_parentLink.m_value == kConnectFourGameBoardValue_Red ? kConnectFourGameBoardValue_Black : kConnectFourGameBoardValue_Red;

			unsigned numRows = m_gameBoard.GetNumRows();
			unsigned numColumns = m_gameBoard.GetNumColumns();
			for (unsigned row = 0; row < numRows; row++)
			{
				for (unsigned column = 0; column < numColumns; column++)
				{
					GameBoardLocation<ConnectFourGameBoardValue> element = m_gameBoard.GetValue(row, column);
					if (element.m_contents == Ai::kConnectFourGameBoardValue_Empty)
					{
						ConnectFourMove Move_t(nextPlayer, row, column);
						ConnectFourGameBoard gameBoard(m_gameBoard);
						gameBoard.SetValue(row, column, nextPlayer);
						children.emplace_back(Move_t, gameBoard);
					}
				}
			}
		}

		void GenerateMoves(std::vector<ConnectFourMove>& moves) const
		{
			// Reverse the player from our parent link to generate the moves for the next ply.
			// TODO Create a new type that exposes not operator.
			ConnectFourGameBoardValue playerValue =
				m_parentLink.m_value == kConnectFourGameBoardValue_Red ? kConnectFourGameBoardValue_Black : kConnectFourGameBoardValue_Red;

			unsigned numRows = m_gameBoard.GetNumRows();
			unsigned numColumns = m_gameBoard.GetNumColumns();
			for (unsigned row = 0; row < numRows; row++)
			{
				for (unsigned column = 0; column < numColumns; column++)
				{
					GameBoardLocation<ConnectFourGameBoardValue> element = m_gameBoard.GetValue(row, column);
					if (element.m_contents == Ai::kConnectFourGameBoardValue_Empty)
					{
						moves.emplace_back(playerValue, row, column);
					}
				}
			}
		}

		ConnectFourTreeNode GenerateChild(const ConnectFourMove& Move_t) const
		{
			ConnectFourTreeNode child(*this);
			child.m_gameBoard.SetValue(Move_t.m_row, Move_t.m_column, Move_t.m_value);
			return child;
		}

		ConnectFourTreeNode GetChild(const ConnectFourMove& Move_t) const
		{
			ConnectFourTreeNode child(*this);
			child.m_gameBoard.SetValue(Move_t.m_row, Move_t.m_column, Move_t.m_value);
			child.m_parentLink = Move_t;
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
		ConnectFourGameBoard m_gameBoard;
		ConnectFourMove m_parentLink;
		int m_maxn;
	};

	typedef Game<ConnectFourNode, ConnectFourMove> TicTacToeNodeVisitor;


	/*
	template< class GameBoard >
	class TicTacToeNodeVisitor : public Game< TicTacToeNodeVisitor<GameBoard> >
	{
	public:
	TicTacToeNodeVisitor(TicTacToeNode<GameBoard> node) : m_node(node) {}

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
