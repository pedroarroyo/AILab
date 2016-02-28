#ifndef AI_GAME_H_
#define AI_GAME_H_

#include <type_traits>
#include <vector>

namespace Ai
{
	template <typename State_t, typename Move_t, typename Player_t>
	struct Game_t
	{
		virtual ~Game_t() = 0;

		virtual std::vector<Move_t> LegalMoves(const State_t& node, const Player_t& player) const = 0;

		virtual State_t MakeMove(const Move_t& move, const State_t& node) const = 0;

		virtual bool TerminalTest(const State_t& node) const = 0;

		virtual int Utility(const State_t& node, const Player_t& player) const = 0;
	};
};

#endif