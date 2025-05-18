#include "Knight.h"

Knight::Knight() {
	this->points = 3;
	this->countMoves = 0;
}

//Knight* Knight::getCopy() const {
//	return new Knight(*this);
//}

char Knight::getDesignation() const {
	return designation;
}

void Knight::checkMoves(std::vector<std::vector<Character*>> board, bool friendlyFire, bool checkRescue) {
	this->moves.clear();
	this->kills.clear();

	getPlayersPositions(board);
	int enemy = 1;
	if (player == 1)
		enemy = 2;
	
	std::vector<int> newPos;

	// row pos, right
	newPos = std::vector<int>{ position[0] + 2, position[1] + 1 };
	if (newPos[0] < 8 && newPos[1] < 8) {
		if (playersPositions[newPos[0]][newPos[1]] == player && friendlyFire)
			this->moves.push_back(newPos);
		if (playersPositions[newPos[0]][newPos[1]] == enemy)
			this->kills.push_back(newPos);
		if (playersPositions[newPos[0]][newPos[1]] != player && playersPositions[newPos[0]][newPos[1]] != enemy)
			this->moves.push_back(newPos);
	}

	// row pos, left
	newPos = std::vector<int>{ position[0] + 2, position[1] - 1 };
	if (newPos[0] < 8 && newPos[1] >= 0) {
		if (playersPositions[newPos[0]][newPos[1]] == player && friendlyFire)
			this->moves.push_back(newPos);
		if (playersPositions[newPos[0]][newPos[1]] == enemy)
			this->kills.push_back(newPos);
		if (playersPositions[newPos[0]][newPos[1]] != player && playersPositions[newPos[0]][newPos[1]] != enemy)
			this->moves.push_back(newPos);
	}

	// row neg, right
	newPos = std::vector<int>{ position[0] - 2, position[1] + 1 };
	if (newPos[0] >= 0 && newPos[1] < 8) {
		if (playersPositions[newPos[0]][newPos[1]] == player && friendlyFire)
			this->moves.push_back(newPos);
		if (playersPositions[newPos[0]][newPos[1]] == enemy)
			this->kills.push_back(newPos);
		if (playersPositions[newPos[0]][newPos[1]] != player && playersPositions[newPos[0]][newPos[1]] != enemy)
			this->moves.push_back(newPos);
	}

	// row neg, left
	newPos = std::vector<int>{ position[0] - 2, position[1] - 1 };
	if (newPos[0] >= 0 && newPos[1] >= 0) {
		if (playersPositions[newPos[0]][newPos[1]] == player && friendlyFire)
			this->moves.push_back(newPos);
		if (playersPositions[newPos[0]][newPos[1]] == enemy)
			this->kills.push_back(newPos);
		if (playersPositions[newPos[0]][newPos[1]] != player && playersPositions[newPos[0]][newPos[1]] != enemy)
			this->moves.push_back(newPos);
	}

	// right, up
	newPos = std::vector<int>{ position[0] - 1, position[1] + 2 };
	if (newPos[0] >= 0 && newPos[1] < 8) {
		if (playersPositions[newPos[0]][newPos[1]] == player && friendlyFire)
			this->moves.push_back(newPos);
		if (playersPositions[newPos[0]][newPos[1]] == enemy)
			this->kills.push_back(newPos);
		if (playersPositions[newPos[0]][newPos[1]] != player && playersPositions[newPos[0]][newPos[1]] != enemy)
			this->moves.push_back(newPos);
	}

	// right, down
	newPos = std::vector<int>{ position[0] + 1, position[1] + 2 };
	if (newPos[0] < 8 && newPos[1] < 8) {
		if (playersPositions[newPos[0]][newPos[1]] == player && friendlyFire)
			this->moves.push_back(newPos);
		if (playersPositions[newPos[0]][newPos[1]] == enemy)
			this->kills.push_back(newPos);
		if (playersPositions[newPos[0]][newPos[1]] != player && playersPositions[newPos[0]][newPos[1]] != enemy)
			this->moves.push_back(newPos);
	}

	// left, up
	newPos = std::vector<int>{ position[0] - 1, position[1] - 2 };
	if (newPos[0] >= 0 && newPos[1] >= 0) {
		if (playersPositions[newPos[0]][newPos[1]] == player && friendlyFire)
			this->moves.push_back(newPos);
		if (playersPositions[newPos[0]][newPos[1]] == enemy)
			this->kills.push_back(newPos);
		if (playersPositions[newPos[0]][newPos[1]] != player && playersPositions[newPos[0]][newPos[1]] != enemy)
			this->moves.push_back(newPos);
	}

	// left, down
	newPos = std::vector<int>{ position[0] + 1, position[1] - 2 };
	if (newPos[0] < 8 && newPos[1] >= 0) {
		if (playersPositions[newPos[0]][newPos[1]] == player && friendlyFire)
			this->moves.push_back(newPos);
		if (playersPositions[newPos[0]][newPos[1]] == enemy)
			this->kills.push_back(newPos);
		if (playersPositions[newPos[0]][newPos[1]] != player && playersPositions[newPos[0]][newPos[1]] != enemy)
			this->moves.push_back(newPos);
	}
}

Knight::~Knight() {}
