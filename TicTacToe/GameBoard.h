// File: Game.h
// Author: Pedro Arroyo
// Description: 
// The "GameBoard" class encapsulates a multidimensional array of tokens representing players. It is suitable for playing any game where tokens are placed in order 
// to indicate ownership of a multidimensional grid.
// Usage:
// Instantiate a GameBoard of a certain specified size. Grid locations can be modified/queried via the SetValue/GetValue methods.

#ifndef GAMEBOARD_H__
#define GAMEBOARD_H__

#include "GameTypes.h"

#include <vector>

class GameBoard
{
public:
	struct Location
	{
		Location( int row, int column ) : m_row(row), m_column(column) {}
		int m_row;
		int m_column;
	};

    GameBoard( uint8_t boardSize );
    ~GameBoard();

    unsigned GetNumOccupiedSquares() const { return m_numOccupiedSquares; }

	uint8_t GetBoardSize() const { return m_boardSize; }
//	void SetBoardSize();

    TicTacToe::PlayerDesignation GetValue(unsigned row, unsigned column) const;
    bool SetValue(unsigned row, unsigned column, TicTacToe::PlayerDesignation value);

	bool IsLocationValid(unsigned row, unsigned column) const;
	bool IsLocationOccupied(unsigned row, unsigned column) const;

    void Draw() const;

private:
	uint8_t m_boardSize;
	std::vector<TicTacToe::PlayerDesignation> m_boardValues;
    unsigned m_numOccupiedSquares;
    TicTacToe::PlayerDesignation m_unoccupiedValue;
};

#endif