// ===========================================================================
// Class: Test
// Description:
// This is the test class to chech and validate the game logic.
// ===========================================================================
#ifndef TEST_H
#define TEST_H

#include "Character.h"
#include<vector>
#include<iostream>

class Test
{
public:
	Test();
	~Test();
	std::vector<std::vector<Character*>>		move(std::vector<std::vector<Character*>> board);
	void										possibleMoves(std::vector<std::vector<Character*>> board);
};

#endif // TEST_H