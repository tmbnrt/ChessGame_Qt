// ===========================================================================
// Class: Player
// Description:
// This is the player class with the actual game points and chess figures left
// ===========================================================================
#ifndef PLAYER_H
#define PLAYER_H

#include "Character.h"
#include "King.h"
#include "Queen.h"
#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"
#include "Pawn.h"

#include<vector>
#include<string>

class Player
{
public:
	Player();
	~Player();

	int											id;
	std::string									color;
	std::string									name;
	std::vector<std::vector<Character*>>		putChars(std::vector<std::vector<Character*>> board);
	//std::vector<std::vector<Character*>>		copy_putChars(std::vector<std::vector<Character*>> copy, int row, int col, Character* to_copy);
	void										assign(std::string name, int id);
	void										kill(std::vector<int> pos);
	std::vector<std::vector<Character*>>		getQueen(std::vector<std::vector<Character*>> board, std::vector<int> pos);

private:
	int											points;
	std::vector<Character>						characters;
	void										initChars();
	void										delCharVecs();
	King										king;
	King										king_copy;
	std::vector<Queen>							queens;
	std::vector<Rook>							rooks;
	std::vector<Knight>							knights;
	std::vector<Bishop>							bishops;
	std::vector<Pawn>							pawns;
};

#endif