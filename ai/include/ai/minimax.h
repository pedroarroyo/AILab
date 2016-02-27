// minimax.h
// Generic implementation of minimax adversarial search.

#ifndef AI_MINIMAX_H_
#define AI_MINIMAX_H_

namespace Ai
{ 
	template <typename State_t, typename Player_t, typename Game_t> 
	int Min(const State_t& node, const Player_t& player, int depth, int a, int b, const Game_t& game)
	{
		if (depth == 0 || game.TerminalTest(node))
		{
			return game.Utility(node, returnMaximum);
		}

		// TODO Make this an iterator/generator
		std::vector<State_t> childNodes;
		node.GenerateChildren(childNodes);
		for (const State_t childNode : childNodes)
		{
			b = std::min(b, Max<State_t, Game_t, Player_t>(childNode, depth - 1, a, b, game));
			if (b <= a)
			{
				return a; // alpha cutoff.
			}
		}
		        	
		return b;
	}

    template <typename State_t, typename Game_t, typename Player_t> 
    int Max(const State_t& node, const Player_t& player, int depth, int a, int b, bool returnMaximum, const Game_t& game)
    {
        if (depth == 0 || game.TerminalTest(node))
        {
            return game.Utility(node, returnMaximum);
        }

        // TODO Make this an iterator/generator
        std::vector<State_t> childNodes;
        node.GenerateChildren(childNodes);
        for (const State_t childNode : childNodes)
        {
            a = std::max(a, Min<State_t, Game_t>(childNode, depth - 1, a, b, game));
            if (b <= a)
            {
                return b; // beta cutoff.
            }
        }

        return a;
	}

	template <typename State_t, typename Move_t, typename Game_t, typename Player> 
	Move_t MiniMax(const State_t& node, const Player& player, int depth, int a, int b, bool returnMaximum, const Game_t& game)
	{
        // Determines the best move.
        int a = -std::numeric_limits<int>::max();
        int b = std::numeric_limits<int>::max();
        int depth = 10;

        Move_t bestMove;
        std::vector<Move_t> moves = game.LegalMoves(node, player);
        for each(const Move_t& move in moves)
        {
            // Generate a child for each move.
            State_t child = tree.GetChild(move);
            int v = Min<Node_t, Game_t, Player>(child, 10, a, b, true, game);
            if (v > a)
            {
                a = v;
                bestMove = Move_t;
            }
        }
	}

	template <class Node, class Game_t> int MiniMax(const Node& node, int depth, int a, int b, bool returnMaximum, Game_t& game)
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
				a = std::max(a, MiniMax<Node, Game_t>(childNode, depth - 1, a, b, !returnMaximum, game));
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
				b = std::min(b, MiniMax<Node, Game_t>(childNode, depth - 1, a, b, !returnMaximum, game));
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