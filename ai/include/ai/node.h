
#ifndef AI_NODE_H_
#define AI_NODE_H_

#include <vector>

namespace Ai
{
	// Actions are the edges of the adversarial search tree.
	class Action
	{

	};

	// A Move_t is a change in the state performable by a player.
	class Move_t
	{

	};

	// A Game encapsulates the heurisstics by which states are evaluated.
	template<class DerivedClass>
	class Node
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

		void GenerateChildren(std::vector<Node>& children) const
		{
			return static_cast<DerivedClass>(this)->GenerateChildren(children);
		}

		Node GetChild(const Action&) const
		{
			return static_cast<DerivedClass>(this)->GetChild(Action);
		}

		int DetermineScore(bool returnMaximum) const
		{
			static_cast<DerivedClass>(this)->DetermineScore(returnMaximum);
		}

		void GenerateMoves(std::vector<Action>& moves) const
		{
			static_cast<DerivedClass>(this)->GenerateChildNodes(moves);
		}

		bool IsTerminal() const
		{
			static_cast<DerivedClass>(this)->IsTerminal();
		}

		bool IsMoveValid(const Action& Move_t)
		{
			static_cast<DerivedClass>(this)->IsMoveValid(Move_t);
		}
	};




	// States define the nodes of the search tree.
	template< class Node, class Action >
	class Game
	{
	public:
		Game(const Node& node) : m_node(node) {}
		//		Node<DerivedClass>& operator*()
		//		{
		//			return *(static_cast<DerivedClass>(this));
		//		}

		//		void ApplyMove(const Action<DerivedClass>& Move_t)
		//		{
		//			static_cast<DerivedClass>(this)->ApplyMove(Move_t);
		//		}

		bool IsTerminal(Node node) const
		{
			return node.IsTerminal();
		}

		int DetermineScore(Node node, bool returnMaximum) const
		{
			return static_cast<DerivedClass>(this)->(node, returnMaximum);
		}

//		void GenerateMoves(std::vector<Action>& moves) const
//		{
//			return m_node.GenerateMoves(moves);
//		}

		Action GetMove() const
		{
			return Action();
		}

		// TODO change this to overloaded dereference operator.
//		const Node& GetNode() const { return node; }

//		bool IsMoveValid(const Action& Move_t) const
//		{
//			return m_node.IsMoveValid(Move_t);
//		}

	private:
//		Node m_node;
		//		std::vector<Action<DerivedClass>> m_moves;
	};




};

#endif
