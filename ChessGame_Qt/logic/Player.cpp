#include "Player.h"

#include<string>

Player::Player() {}

void Player::assign(std::string name, int id) {
	this->name = name;
	this->id = id;
	if (id == 1)
		this->color = "White";
	else
		this->color = "Black";

	initChars();

	// count points
	// ... loop
}

void Player::initChars() {
	if (color == "White") {
		this->king = King();
		//this->king = new King();
		this->king.assign('K', 1);

		this->queens = std::vector<Queen>{ Queen(), Queen(), Queen(), Queen()};
		//this->queens = std::vector<Queen*>{ new Queen() };
		this->queens[0].assign('D', 1);
		this->queens[1].assign('D', 1);
		this->queens[2].assign('D', 1);
		this->queens[3].assign('D', 1);

		this->rooks = std::vector<Rook>{ Rook(), Rook() };
		//this->rooks = std::vector<Rook*>{ new Rook(), new Rook() };
		this->rooks[0].assign('T', 1);
		this->rooks[1].assign('T', 1);

		this->knights = std::vector<Knight>{ Knight(), Knight() };
		//this->knights = std::vector<Knight*>{ new Knight(), new Knight() };
		this->knights[0].assign('S', 1);
		this->knights[1].assign('S', 1);

		this->bishops = std::vector<Bishop>{ Bishop(), Bishop() };
		//this->bishops = std::vector<Bishop*>{ new Bishop(), new Bishop() };
		this->bishops[0].assign('L', 1);
		this->bishops[1].assign('L', 1);

		this->pawns = std::vector<Pawn>{ Pawn(), Pawn(), Pawn(), Pawn(), Pawn(), Pawn(), Pawn(), Pawn() };
		//this->pawns = std::vector<Pawn*>{ new Pawn(), new Pawn(), new Pawn(), new Pawn(), new Pawn(), new Pawn(), new Pawn(), new Pawn() };
		for (int i = 0; i < pawns.size(); i++)
			this->pawns[i].assign('B', 1);
	}
	else {
		this->king = King();
		//this->king = new King();
		this->king.assign('k', 2);

		this->queens = std::vector<Queen> { Queen(), Queen(), Queen(), Queen()};
		//this->queens = std::vector<Queen*> { new Queen() };
		this->queens[0].assign('d', 2);
		this->queens[1].assign('d', 2);
		this->queens[2].assign('d', 2);
		this->queens[3].assign('d', 2);

		this->rooks = std::vector<Rook>{ Rook(), Rook() };
		//this->rooks = std::vector<Rook*>{ new Rook(), new Rook() };
		this->rooks[0].assign('t', 2);
		this->rooks[1].assign('t', 2);

		this->knights = std::vector<Knight>{ Knight(), Knight() };
		//this->knights = std::vector<Knight*>{ new Knight(), new Knight() };
		this->knights[0].assign('s', 2);
		this->knights[1].assign('s', 2);

		this->bishops = std::vector<Bishop>{ Bishop(), Bishop() };
		//this->bishops = std::vector<Bishop*>{ new Bishop(), new Bishop() };
		this->bishops[0].assign('l', 2);
		this->bishops[1].assign('l', 2);

		this->pawns = std::vector<Pawn>{ Pawn(), Pawn(), Pawn(), Pawn(), Pawn(), Pawn(), Pawn(), Pawn() };
		//this->pawns = std::vector<Pawn*>{ new Pawn(), new Pawn(), new Pawn(), new Pawn(), new Pawn(), new Pawn(), new Pawn(), new Pawn() };
		for (int i = 0; i < pawns.size(); i++)
			this->pawns[i].assign('b', 2);
	}
}

std::vector<std::vector<Character*>> Player::putChars(std::vector<std::vector<Character*>> board) {
	// STRUCTURE
	// [0,0] [0,1] [0,2]
	// [1,0] [1,1] [1,2]
	// [2,0] [2,1] [2,2]
	if (color == "White") {
		king.defPosition(std::vector<int> {7, 4});
		board[7][4] = &king;
		queens[0].defPosition(std::vector<int> {7, 3});
		queens[1].defPosition(std::vector<int> {8, 8});
		queens[2].defPosition(std::vector<int> {8, 8});
		queens[3].defPosition(std::vector<int> {8, 8});
		board[7][3] = &queens[0];
		bishops[0].defPosition(std::vector<int> {7, 2});
		board[7][2] = &bishops[0];
		bishops[1].defPosition(std::vector<int> {7, 5});
		board[7][5] = &bishops[1];
		knights[0].defPosition(std::vector<int> {7, 1});
		board[7][1] = &knights[0];
		knights[1].defPosition(std::vector<int> {7, 6});
		board[7][6] = &knights[1];
		rooks[0].defPosition(std::vector<int> {7, 0});
		board[7][0] = &rooks[0];
		rooks[1].defPosition(std::vector<int> {7, 7});
		board[7][7] = &rooks[1];
		for (int i = 0; i < pawns.size(); i++) {
			pawns[i].defPosition(std::vector<int> {6, i});
			board[6][i] = &pawns[i];
		}			
	}
	else {
		king.defPosition(std::vector<int> {0, 4});
		board[0][4] = &king;
		queens[0].defPosition(std::vector<int> {0, 3});
		board[0][3] = &queens[0];
		bishops[0].defPosition(std::vector<int> {0, 2});
		board[0][2] = &bishops[0];
		bishops[1].defPosition(std::vector<int> {0, 5});
		board[0][5] = &bishops[1];
		knights[0].defPosition(std::vector<int> {0, 1});
		board[0][1] = &knights[0];
		knights[1].defPosition(std::vector<int> {0, 6});
		board[0][6] = &knights[1];
		rooks[0].defPosition(std::vector<int> {0, 0});
		board[0][0] = &rooks[0];
		rooks[1].defPosition(std::vector<int> {0, 7});
		board[0][7] = &rooks[1];		
		for (int i = 0; i < pawns.size(); i++) {
			pawns[i].defPosition(std::vector<int> {1, i});
			board[1][i] = &pawns[i];			
		}
	}

	return board;
}

void Player::delCharVecs() {
	this->rooks.clear();
	this->knights.clear();
	this->knights.clear();
	this->queens.clear();
	this->pawns.clear();
}

/*
std::vector<std::vector<Character*>> Player::copy_putChars(std::vector<std::vector<Character*>> copy, int row, int col, Character* to_copy) {
	
	if (to_copy->getDesignation() == 'B' || to_copy->getDesignation() == 'b') {
		pawns[0].defPosition(std::vector<int> {row, col});
		copy[row][col] = &pawns[0];
	}

	if (to_copy->getDesignation() == 'T' || to_copy->getDesignation() == 't') {
		rooks[0].defPosition(std::vector<int> {row, col});
		copy[row][col] = &rooks[0];
	}

	if (to_copy->getDesignation() == 'S' || to_copy->getDesignation() == 's') {
		knights[0].defPosition(std::vector<int> {row, col});
		copy[row][col] = &knights[0];
	}

	if (to_copy->getDesignation() == 'L' || to_copy->getDesignation() == 'l') {
		bishops[0].defPosition(std::vector<int> {row, col});
		copy[row][col] = &bishops[0];
	}

	if (to_copy->getDesignation() == 'D' || to_copy->getDesignation() == 'd') {
		queens[0].defPosition(std::vector<int> {row, col});
		copy[row][col] = &queens[0];
	}

	//if (to_copy->getDesignation() == 'K' || to_copy->getDesignation() == 'k') {
	//	king.defPosition(std::vector<int> {row, col});
	//	copy[row][col] = &king;
	//}

	return copy;
}*/

std::vector<std::vector<Character*>> Player::getQueen(std::vector<std::vector<Character*>> board, std::vector<int> pos) {
	board[pos[0]][pos[1]] = nullptr;
	for (int i = 0; i < queens.size(); i++) {
		if (queens[i].getPosition()[0] == 8) {
			queens[i].defPosition(pos);
			board[pos[0]][pos[1]] = &queens[i];
			return board;
		}
	}
}

void Player::kill(std::vector<int> pos) {
	// loop through characters and delete character with designatuion "c"
	// ...
}

Player::~Player() {}
