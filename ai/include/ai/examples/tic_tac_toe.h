#ifndef AI_EXAMPLES_TICTACTOE_H_
#define AI_EXAMPLES_TICTACTOE_H_

#include "game_board.h"
#include "ai/game.h"
#include "ai/node.h"

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
		kTicTacToeMoveResult_Invalid,
		kTicTacToeMoveResult_None,
		kTicTacToeMoveResult_Victory,
		kTicTacToeMoveResult_Draw
	};

	typedef GameBoardLocation<TicTacToePlayer> TicTacToeGameBoardLocation;
	typedef GameBoard<TicTacToePlayer, 3, 3> TicTacToeGameBoard_t;

	class TicTacToeGameBoard : public TicTacToeGameBoard_t
	{
	public: 
		TicTacToeGameBoard() : TicTacToeGameBoard_t(kTicTacToeGameBoardValue_Empty) {}
	};

	// Forward declarations.
	class TicTacToeNode;
	class TicTacToeMove;

	// Helpers
	TicTacToeMoveResult TicTacToeAnalyzeMove(const TicTacToeGameBoard& gameBoard, const TicTacToeMove& Move_t);

	// Classes
	class TicTacToeMove : public Ai::Action
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

	class TicTacToeTreeNode : public Ai::Node< TicTacToeNode >
	{
	public:
		// TODO - How do we handle passing in undefined board value?
		TicTacToeTreeNode(TicTacToePlayer initialPlayer, TicTacToeGameBoard gameBoard ) 
			: m_parentLink( (initialPlayer == kTicTacToeGameBoardValue_O) ?  kTicTacToeGameBoardValue_X : kTicTacToeGameBoardValue_O, 0, 0) 
			, m_gameBoard(gameBoard) {}

		TicTacToeTreeNode(TicTacToeMove Move_t, TicTacToeGameBoard gameBoard)
			: m_parentLink(Move_t)
			, m_gameBoard(gameBoard) {}

		void GenerateChildren(std::vector<TicTacToeTreeNode>& children) const
		{
			// Reverse the player from our parent link to generate the moves for the next ply.
			// TODO Create a new type that exposes not operator.
			TicTacToePlayer nextPlayer =
				m_parentLink.m_value == kTicTacToeGameBoardValue_O ? kTicTacToeGameBoardValue_X : kTicTacToeGameBoardValue_O;

			unsigned numRows = m_gameBoard.GetNumRows();
			unsigned numColumns = m_gameBoard.GetNumColumns();
			for (unsigned row = 0; row < numRows; row++)
			{
				for (unsigned column = 0; column < numColumns; column++)
				{
					GameBoardLocation<TicTacToePlayer> element = m_gameBoard.GetValue(row, column);
					if (element.m_contents == Ai::kTicTacToeGameBoardValue_Empty)
					{
						TicTacToeMove Move_t(nextPlayer, row, column);
						TicTacToeGameBoard gameBoard(m_gameBoard);
						gameBoard.SetValue(row, column, nextPlayer);
						children.emplace_back(Move_t, gameBoard);
					}
				}
			}
		}

		void GenerateMoves(std::vector<TicTacToeMove>& moves) const
		{
			// Reverse the player from our parent link to generate the moves for the next ply.
			// TODO Create a new type that exposes not operator.
			TicTacToePlayer playerValue =
				m_parentLink.m_value == kTicTacToeGameBoardValue_O ? kTicTacToeGameBoardValue_X : kTicTacToeGameBoardValue_O;

			unsigned numRows = m_gameBoard.GetNumRows();
			unsigned numColumns = m_gameBoard.GetNumColumns();
			for (unsigned row = 0; row < numRows; row++)
			{
				for (unsigned column = 0; column < numColumns; column++)
				{
					GameBoardLocation<TicTacToePlayer> element = m_gameBoard.GetValue(row, column);
					if (element.m_contents == Ai::kTicTacToeGameBoardValue_Empty)
					{
						moves.emplace_back(playerValue, row, column);
					}
				}
			}
		}

		TicTacToeTreeNode GenerateChild( const TicTacToeMove& Move_t ) const
		{
			TicTacToeTreeNode child(*this);
			child.m_gameBoard.SetValue(Move_t.m_row, Move_t.m_column, Move_t.m_value);
			return child;
		}

		TicTacToeTreeNode GetChild(const TicTacToeMove& Move_t) const
		{
			TicTacToeTreeNode child(*this);
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
//	private:
		TicTacToeGameBoard m_gameBoard;
		TicTacToeMove m_parentLink;
		int m_maxn;
	};

	typedef Game<TicTacToeNode, TicTacToeMove> TicTacToe;
	
	struct TicTacToePolicy : public Game_t<TicTacToeTreeNode, TicTacToeMove, TicTacToePlayer>
	{
		virtual ~TicTacToePolicy() { ; }

		virtual std::vector<TicTacToeMove> LegalMoves(const TicTacToeTreeNode& node, const TicTacToePlayer& player) override 
		{
			std::vector<TicTacToeMove> moves;

			// Reverse the player from our parent link to generate the moves for the next ply.
			// TODO Create a new type that exposes not operator.
			TicTacToePlayer nextPlayer =
				node.m_parentLink.m_value == kTicTacToeGameBoardValue_O ? kTicTacToeGameBoardValue_X : kTicTacToeGameBoardValue_O;

			unsigned numRows = node.m_gameBoard.GetNumRows();
			unsigned numColumns = node.m_gameBoard.GetNumColumns();
			for (unsigned row = 0; row < numRows; row++)
			{
				for (unsigned column = 0; column < numColumns; column++)
				{
					GameBoardLocation<TicTacToePlayer> element = node.m_gameBoard.GetValue(row, column);
					if (element.m_contents == Ai::kTicTacToeGameBoardValue_Empty)
					{
						TicTacToeMove Move_t(nextPlayer, row, column);
						TicTacToeGameBoard gameBoard(node.m_gameBoard);
						gameBoard.SetValue(row, column, nextPlayer);
						moves.emplace_back(Move_t);
					}
				}
			}

			return moves;
		};

		virtual TicTacToeTreeNode MakeMove(const TicTacToeMove& Move_t, const TicTacToeTreeNode& node) override 
		{
			TicTacToeTreeNode child(node);
			child.m_gameBoard.SetValue(Move_t.m_row, Move_t.m_column, Move_t.m_value);
			return child;
		};

		bool TerminalTest(const TicTacToeTreeNode& node) override
		{
			TicTacToeMoveResult result = TicTacToeAnalyzeMove(node.m_gameBoard, node.m_parentLink);
			return (result == kTicTacToeMoveResult_Draw || result == kTicTacToeMoveResult_Victory);
		}

		int Utility(const TicTacToeTreeNode& node, bool returnMaximum) override
		{
			const TicTacToeMoveResult result = TicTacToeAnalyzeMove(node.m_gameBoard, node.m_parentLink);

			if (result == kTicTacToeMoveResult_Victory)
			{
				return returnMaximum ? 1 : -1;
			}

			return 0;
		}
	};




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
