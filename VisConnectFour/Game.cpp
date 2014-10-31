#include "StdAfx.h"

#include "Game.h"

//#include "curses.h"
#include <assert.h>
#include "Vis/AsciiCanvas.h"
#include "Ai/Examples/ConnectFour.h"
#include "Player.h"
extern "C"
{
	#include "pdcurses/curses.h"
}


// 6 characters that make up our 4x2 circular game piece.
static const char kCircle10 = 128i8;
static const char kCircle20 = 129i8;
static const char kCircle30 = 130i8;
static const char kCircle40 = 131i8;
static const char kCircle11 = 132i8;
static const char kCircle21 = 133i8;
static const char kCircle31 = 134i8;
static const char kCircle41 = 135i8;

static const char kSpriteDataGamePiece[] = {
	kCircle10, kCircle20, kCircle30, kCircle40,
	kCircle11, kCircle21, kCircle31, kCircle41 };
const Vis::AsciiSprite Game::kSpriteGamePiece(kSpriteDataGamePiece, 4, 2);

namespace
{
	void Draw_(WINDOW* menu_win, const Util::Vector2<unsigned>& upperLeft, const Vis::AsciiSprite& sprite)
	{

		start_color();
		init_pair(2, COLOR_GREEN, COLOR_BLACK);
		attron(COLOR_PAIR(2));
//		attron(A_REVERSE);
		box(menu_win, 0, 0);

		// PLA_TODO Switch this to use memcopy.
		unsigned width = sprite.GetWidth();
		unsigned height = sprite.GetHeight();
		for (unsigned x = 0;  x < width; x++)
		{
			for (unsigned y = 0; y < height; y++)
			{
//				m_charArray.Set(upperLeft.m_x + column, upperLeft.m_y + row, sprite.GetValue(column, row));
				// Curses expects coordinates in "row, column" format.
//				mvwprintw(menu_win, upperLeft.m_y + y, upperLeft.m_x + x, "%c", sprite.GetValue(x, y));
				mvwprintw(menu_win, upperLeft.m_y + y, upperLeft.m_x + x, "%c", sprite.GetValue(x, y));
			}
		}

		//		box(child, 0, 0);


		/*
		int x, y, i;

		x = 2;
		y = 2;
		for (i = 0; i < n_choices; ++i)
		{
			if (highlight == i + 1)
			{
				wattron(menu_win, A_REVERSE);
				mvwprintw(menu_win, y, x, "%s", choices[i]);
				wattroff(menu_win, A_REVERSE);
			}
			else
				mvwprintw(menu_win, y, x, "%s", choices[i]);
			++y;
		}
		wrefresh(menu_win);
*/
	}

}

Game::Game(WINDOW** win)
	: m_state(&m_stateIdle)
{
	// Creates a subwindow per column (allows us to draw borders and do hit detection.
	unsigned numRows = m_gameBoard.GetNumRows();
	unsigned numColumns = m_gameBoard.GetNumColumns();
	unsigned gamePieceHeight = kSpriteGamePiece.GetHeight();
	unsigned gamePieceWidth = kSpriteGamePiece.GetWidth();

	// Resize window to accommodate the game board.
	*win = newwin(((gamePieceHeight + 1) * numRows) +1, ((gamePieceWidth + 1) * numColumns) + 1, 0, 0);
//	win = newwin(30, 10, 0, 0);

//	wresize(&win, gamePieceWidth * numColumns, gamePieceHeight * numRows);
	box(*win, 0, 0);

	int width, height, bx, by, sw, sh, i, c, num;
	getmaxyx(*win, height, width);
	getbegyx(*win, by, bx);

	// Creates a subwindow per column.
	for (int i = 0; i < numColumns; i++)
	{
		WINDOW* child = derwin(*win, height, gamePieceWidth + 2, 0, 0);
		box(child, 0, 0);
		m_columnWindows.push_back(child);
	}

	sw = width / 3;
	sh = height / 3;
//	WINDOW* subWin;
//	if (( subWin = subwin(&win, sh, sw, by + h - sh - 2, bx + w - sw - 2)) == NULL)
//		return;

//	box(subWin, 0, 0);
}

void OnMouseEvent(const MEVENT& event)
{
	int i, j, choice;

	i = startx + 2;
	j = starty + 3;

	for (choice = 0; choice < n_choices; ++choice)
		if (mouse_y == j + choice && mouse_x >= i && mouse_x <= i + strlen(choices[choice]))
		{
		if (choice == n_choices - 1)
			*p_choice = -1;
		else
			*p_choice = choice + 1;
		break;
		}

}

/*
Ai::TicTacToeMoveResult Game::ProcessTurn( Ai::TicTacToeGameBoardValue player, PlayerStrategy& strategy )
{
	// Determines current player move.
	unsigned row = 0, column = 0;
	strategy.DetermineMove( m_lastMove, player, m_gameBoard, row, column );
	m_lastMove.m_value = player;
	m_lastMove.m_row = row;
	m_lastMove.m_column = column;

	bool isValid = m_gameBoard.SetValue(row, column, player);
	if(!isValid)
	{
		return Ai::kTicTacToeMoveResult_Invalid;
	}
	else
	{
		return Ai::TicTacToeAnalyzeMove(m_gameBoard, m_lastMove);
	}	
}
*/

void Game::DrawGame(WINDOW* window) const
{
	// Tiles game pieces in the background color to draw the gameboard.
	// TODO - Add a better location iterator to gameboard.
	unsigned numRows = m_gameBoard.GetNumRows();
	unsigned numColumns = m_gameBoard.GetNumColumns();
	unsigned upperLeftX = 1;
	unsigned upperLeftY = 1;
	for (unsigned row = 0; row < numRows; row++)
	{
		for (unsigned column = 0; column < numColumns; column++)
		{
			Draw_(window, Util::Vector2<unsigned>(upperLeftX, upperLeftY), kSpriteGamePiece);
			upperLeftX += kSpriteGamePiece.GetWidth() + 1;
		}
		upperLeftX = 1;
		upperLeftY += kSpriteGamePiece.GetHeight() + 1;
	}

	for (WINDOW* win : m_columnWindows)
	{
		box(win, 0, 0);
	}

	/*
	// Overlays the game pieces
	unsigned boardSize = m_gameBoard.GetNumColumns();
	
	unsigned spriteX = 0;
	unsigned spriteY = 0;

	for( unsigned row = 0; row < boardSize; row++ )
	{
		spriteX = 0;
		for( unsigned column = 0; column < boardSize; column++ )
		{
			Ai::TicTacToeGameBoardLocation location = m_gameBoard.GetValue(row, column);
			Ai::TicTacToeGameBoardValue value = location.m_contents;
			if(  value == Ai::kTicTacToeGameBoardValue_X )
			{
				canvas.Draw( Util::Vector2<unsigned>( spriteX, spriteY ), kSpriteX );
			}
			else if( value == Ai::kTicTacToeGameBoardValue_O )
			{
				canvas.Draw( Util::Vector2<unsigned>( spriteX, spriteY ), kSpriteO );
			}

			spriteX += 7; 
		}

		spriteY += 6; 
	}
	*/
}
