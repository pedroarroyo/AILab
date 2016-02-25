#ifndef AI_GAME_H_
#define AI_GAME_H_

#include <type_traits>

namespace Ai
{
	template <class Node>
	struct GamePolicy
	{
		virtual ~GamePolicy() = 0;

		virtual bool TerminalTest(const Node& node) = 0;

		// TODO pla - change return maximum to pass in a representation of the player.
		virtual int Utility(const Node& node, bool returnMaximum) = 0;
	};
};

#endif