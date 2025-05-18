#ifndef PLAYERMOVES_H
#define PLAYERMOVES_H

#include "Character.h"
#include "Queen.h"
#include <vector>
#include <iostream>

class PlayerMoves
{
public:
	PlayerMoves();
	~PlayerMoves();
	//int											player;
	bool										checkAllowedActual(std::vector<int> actual);
	bool										checkAllowedTarget(std::vector<int> target);
	bool										checkAllowed(std::vector<int> actual, std::vector<int> target);
	void										clear();
	void										checkPlayerMoves(std::vector<std::vector<Character*>> board, int player);
	void										addHistory(std::vector<int> actual, std::vector<int> target);
	std::vector<std::vector<int>>				getTargets(std::vector<int> actual);
	int											getNumberMoves();
	std::vector<int>							getRandFrom(int act);
	std::vector<int>							getRandTarget(int act);
	bool										isChess() const;
	bool										checkMate();

private:
	std::vector<std::vector<int>>				from;
	std::vector<std::vector<int>>				to;
	std::vector<std::vector<int>>				history_from;
	std::vector<std::vector<int>>				history_to;
	bool										chess;
	bool										isSuizide(std::vector<std::vector<Character*>> board, int player, std::vector<int> actual, std::vector<int> target);
};

#endif PLAYERMOVES_H