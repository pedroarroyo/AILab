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
			return game.Utility(node, player);
		}

		// TODO Make this an iterator/generator
		std::vector<State_t> childNodes;
		node.GenerateChildren(childNodes);
		for (const State_t childNode : childNodes)
		{
			b = std::min<int>(b, Max<State_t, Player_t, Game_t>(childNode, player, depth - 1, a, b, game));
			if (b <= a)
			{
				return a; // alpha cutoff.
			}
		}
		        	
		return b;
	}

    template <typename State_t, typename Player_t, typename Game_t> 
    int Max(const State_t& node, const Player_t& player, int depth, int a, int b, const Game_t& game)
    {
        if (depth == 0 || game.TerminalTest(node))
        {
            return game.Utility(node, player);
        }

        // TODO Make this an iterator/generator
        std::vector<State_t> childNodes;
        node.GenerateChildren(childNodes);
        for (const State_t childNode : childNodes)
        {
            a = std::max(a, Min<State_t, Player_t, Game_t>(childNode, player, depth - 1, a, b, game));
            if (b <= a)
            {
                return b; // beta cutoff.
            }
        }

        return a;
	}

	template <typename State_t, typename Move_t, typename Game_t, typename Player_t> 
	Move_t MiniMax(const State_t& state, const Player_t& player, int depth, const Game_t& game)
	{
        // Determines the best move.
        int a = -std::numeric_limits<int>::max();
        int b = std::numeric_limits<int>::max();

        Move_t bestMove;
        std::vector<Move_t> moves = game.LegalMoves(state, player);
        for each(const Move_t& move in moves)
        {
            // Generate a child for each move.
            State_t child = state.GetChild(move);
            int v = Min<State_t, Player_t, Game_t>(child, player, depth, a, b, game);
            if (v > a)
            {
                a = v;
                bestMove = move;
            }
        }

        return bestMove;
	}
}

#endif