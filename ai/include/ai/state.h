
#ifndef AI_GAME_TREE_H_
#define AI_GAME_TREE_H_

#include <vector>

namespace Ai
{
	// Moves are the edges of the game tree node. It defines a transition from parent to child.
	class GameTreeMove
	{

	};

	template<class DerivedClass>
	class GameTreeNode
	{
	private:
		struct generator 
		{
			generator() : _n{ 0 }, _ln{ 0 } {}
			generator(int n) : _n{ n }, _ln{ 0 } {}

			generator & operator*() {
//				return node;
				return _n;
			}

			bool operator!=(const generator & other) const {
				return _n <= other._n;
			}

			generator& operator++() {
				int temp = _ln + _n;
				_ln = _n;
				_n = temp;
				return *this;
			}
			
		private:
			int _n, _ln;
			DerivedClass node;
		};
		
	public:
		generator begin() const 
		{
			return generator(1);
		}
		generator end() const 
		{
			return generator(1);
		}

		void GenerateChildren(std::vector<GameTreeNode>& children) const
		{
			return static_cast<DerivedClass>(this)->GenerateChildren(children);
		}

		GameTreeNode GetChild(const GameTreeMove& ) const
		{
			return static_cast<DerivedClass>(this)->GetChild(GameTreeMove);
		}

		int DetermineScore( bool returnMaximum ) const
		{
			static_cast<DerivedClass>(this)->DetermineScore(returnMaximum);
 		}

		void GenerateMoves(std::vector<GameTreeMove>& moves) const
		{
			static_cast<DerivedClass>(this)->GenerateChildNodes(moves);
		}

		bool IsTerminal() const
		{
			static_cast<DerivedClass>(this)->IsTerminal();
		}

		bool IsMoveValid(const GameTreeMove& move)
		{
			static_cast<DerivedClass>(this)->IsMoveValid(move);
		}
	};

	template< class GameTreeNode, class GameTreeMove >
	class GameTreeNodeVisitor
	{
	public:
		GameTreeNodeVisitor(const GameTreeNode& node) : m_node(node) {}
//		GameTreeNode<DerivedClass>& operator*()
//		{
//			return *(static_cast<DerivedClass>(this));
//		}

//		void ApplyMove(const GameTreeMove<DerivedClass>& move)
//		{
//			static_cast<DerivedClass>(this)->ApplyMove(move);
//		}

		bool IsTerminal() const
		{
			return m_node.IsTerminal();
		}

		int DetermineScore(bool returnMaximum) const
		{
			return m_node.DetermineScore(returnMaximum);
		}

		void GenerateMoves(std::vector<GameTreeMove>& moves) const
		{
			return m_node.GenerateMoves(moves);
		}

		GameTreeMove GetMove() const
		{
			return GameTreeMove();
		}

		// TODO change this to overloaded dereference operator.
		const GameTreeNode& GetNode() const { return node; } 

		bool IsMoveValid(const GameTreeMove& move) const
		{
			return m_node.IsMoveValid(move);
		}

	private:
		GameTreeNode m_node;
//		std::vector<GameTreeMove<DerivedClass>> m_moves;
	};
};

#endif
