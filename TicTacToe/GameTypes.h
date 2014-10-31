// File: GameTypes.h
// Author: Pedro Arroyo
// Description: Project-wide include file.

#ifndef GAMETYPES_H_
#define GAMETYPES_H_

#include<cstdint>

namespace TicTacToe
{
	enum PlayerDesignation : char
	{
		kPlayerX = 'X',
		kPlayerO = 'O',
		kInvalidPlayer = ' ',
	};
}

#endif