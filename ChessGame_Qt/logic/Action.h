// ===========================================================================
// Class: Action
// Description:
// This class is the communication and instruction interface for both players,
// playing on the console.
// ===========================================================================
#ifndef ACTION_H
#define ACTION_H

#include "Character.h"
#include "PlayerMoves.h"
#include <vector>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <ctime>

class Action
{
public:
	Action();
	~Action();
	//std::vector<std::vector<int>>				getMoves(int player);
	//void										updateMoves(PlayerMoves playerMoves, int player);
	void										printBoard(std::vector<std::vector<Character*>> board);
	void										moveFromConsole(int player, PlayerMoves& playerMoves);
	void										createRandomMove(PlayerMoves playerMoves);
	std::vector<int>							from;
	std::vector<int>							to;
	std::vector<int>							random_from;
	std::vector<int>							random_to;

private:
	std::vector<std::vector<int>>				charBoard;
	//PlayerMoves									movesPlayer_1;
	//PlayerMoves									movesPlayer_2;
};

#endif ACTION_H