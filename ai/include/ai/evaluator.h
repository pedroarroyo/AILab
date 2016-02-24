// Evaluator.h
// Evaluators are implementations of various AI algorithms.

#ifndef AI_EVALUATOR_H_
#define AI_EVALUATOR_H_

#include "Visitor.h"

namespace Ai
{ 
	template <class Node> int MiniMax(const Node& node, int depth, int a, int b, bool returnMaximum)
	{
		if (depth == 0 || node.IsTerminal())
		{
			return node.DetermineScore(returnMaximum);
		}

		// TODO Make this an iterator/generator
		std::vector<Node> childNodes;
		node.GenerateChildren(childNodes);
		if (returnMaximum)
		{
			for (const Node childNode : childNodes)
			{
				a = std::max(a, MiniMax(childNode, depth - 1, a, b, !returnMaximum));
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
				b = std::min(b, MiniMax(childNode, depth - 1, a, b, !returnMaximum));
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