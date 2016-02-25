// Evaluator.h
// Evaluators are implementations of various AI algorithms.

#ifndef AI_MINIMAX_H_
#define AI_MINIMAX_H_

namespace Ai
{ 
	template <class Node, class GamePolicy> int MiniMax(const Node& node, int depth, int a, int b, bool returnMaximum, GamePolicy& game)
	{
		if (depth == 0 || game.TerminalTest(node))
		{
			return game.Utility(node, returnMaximum);
		}

		// TODO Make this an iterator/generator
		std::vector<Node> childNodes;
		node.GenerateChildren(childNodes);
		if (returnMaximum)
		{
			for (const Node childNode : childNodes)
			{
				a = std::max(a, MiniMax<Node, GamePolicy>(childNode, depth - 1, a, b, !returnMaximum, game));
				if (b <= a)
				{
					return b; // beta cutoff.
				}
			}

			return a;
		}
		else
		{
			for (const Node childNode : childNodes)
			{
				b = std::min(b, MiniMax<Node, GamePolicy>(childNode, depth - 1, a, b, !returnMaximum, game));
				if (b <= a)
				{
					return a; // alpha cutoff.
				}
			}

			return b;
		}
	}
}

#endif