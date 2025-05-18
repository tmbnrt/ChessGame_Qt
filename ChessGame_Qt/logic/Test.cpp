#include "Test.h"

Test::Test() {}


std::vector<std::vector<Character*>> Test::move(std::vector<std::vector<Character*>> board) {
	// TEST MOVES
	board = board[6][3]->move(board, std::vector<int> {5, 3});
	board = board[1][2]->move(board, std::vector<int> {2, 2});
	board = board[6][7]->move(board, std::vector<int> {5, 7});
	board = board[0][3]->move(board, std::vector<int> {3, 0});

	return board;
}

void Test::possibleMoves(std::vector<std::vector<Character*>> board) {
	// CHECK POSSIBLE MOVES
	board[4][3]->checkMoves(board);
	//board[5][5]->checkMoves(board);

	std::vector<std::vector<int>> king_moves = board[4][3]->getMoves();
	std::vector<std::vector<int>> king_kills = board[4][3]->getKills();
	//std::vector<std::vector<int>> queen_moves = board[5][5]->getMoves();
	//std::vector<std::vector<int>> queen_kills = board[5][5]->getKills();
}

Test::~Test(){}