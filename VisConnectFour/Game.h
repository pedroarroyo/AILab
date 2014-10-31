
#ifndef GAME_H_
#define GAME_H_

extern"C"
{
	#include "pdcurses/curses.h"
}

#include "AI/Examples/ConnectFour.h"
#include "Vis/AsciiSprite.h"

namespace Vis
{
	class AsciiCanvas;
}

class Game
{
public:
	Game(WINDOW** win);
	~Game() {}

	static const Vis::AsciiSprite kSpriteGamePiece;
	//	static const AsciiSprite kSpriteGameBoard;

	// Events
	void OnMouseEvent(const MEVENT& mouseEvent);

	void DrawGame(WINDOW* window) const;

private:
	// Basic state machine 
	class State
	{
	public:
		virtual void OnMouseEvent(const MEVENT& mouseEvent) { ; }
	};

	class StateIdle : public State
	{
	};

	class StateWaitingForPlayerInput : public State
	{
	public:
		virtual void OnMouseEvent(const MEVENT& mouseEvent) override;
	};

	// Current game state
	State* m_state;

	State m_stateIdle;
	State m_stateWaitingForPlayerInput;

	Ai::ConnectFourGameBoard m_gameBoard;
	std::vector<WINDOW*> m_columnWindows;
};


#endif