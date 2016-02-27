#ifndef AI_GAME_H_
#define AI_GAME_H_

#include <type_traits>
#include <vector>

namespace Ai
{
	template <typename Node, typename Move_t, typename Player>
	struct Game_t
	{
		virtual ~Game_t() = 0;

		virtual std::vector<Move_t> LegalMoves(const Node& node, const Player& player) = 0;

		virtual Node MakeMove(const Move_t& Move_t, const Node& node) = 0;

		virtual bool TerminalTest(const Node& node) = 0;

		// TODO pla - change return maximum to pass in a representation of the player.
		virtual int Utility(const Node& node, bool returnMaximum) = 0;


	};
};

#endif