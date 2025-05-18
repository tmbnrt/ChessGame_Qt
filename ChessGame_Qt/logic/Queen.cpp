#include "Queen.h"

Queen::Queen() {
	this->points = 9;
	this->countMoves = 0;
}

//Queen* Queen::getCopy() const {
//	return new Queen(*this);
//}

void Queen::checkMoves(std::vector<std::vector<Character*>> board, bool friendlyFire, bool checkRescue) {
	this->moves.clear();
	this->kills.clear();

	getPlayersPositions(board);
	int enemy = 1;
	if (player == 1)
		enemy = 2;

	// pos col
	for (int i = 1; i < 8; i++) {
		std::vector<int> newPos = std::vector<int>{ position[0], position[1] + i };
		if (newPos[1] < 8) {
			if (playersPositions[newPos[0]][newPos[1]] == player) {
				if (friendlyFire)
					this->moves.push_back(newPos);
				break;
			}
			if (playersPositions[newPos[0]][newPos[1]] == enemy) {
				this->kills.push_back(newPos);
				break;
			}
			this->moves.push_back(newPos);
		}
	}

	// neg col
	for (int i = 1; i < 8; i++) {
		std::vector<int> newPos = std::vector<int>{ position[0], position[1] - i };
		if (newPos[1] >= 0) {
			if (playersPositions[newPos[0]][newPos[1]] == player) {
				if (friendlyFire)
					this->moves.push_back(newPos);
				break;
			}
			if (playersPositions[newPos[0]][newPos[1]] == enemy) {
				this->kills.push_back(newPos);
				break;
			}
			this->moves.push_back(newPos);
		}
	}

	// pos row
	for (int i = 1; i < 8; i++) {
		std::vector<int> newPos = std::vector<int>{ position[0] + i, position[1] };
		if (newPos[0] < 8) {
			if (playersPositions[newPos[0]][newPos[1]] == player) {
				if (friendlyFire)
					this->moves.push_back(newPos);
				break;
			}
			if (playersPositions[newPos[0]][newPos[1]] == enemy) {
				this->kills.push_back(newPos);
				break;
			}
			this->moves.push_back(newPos);
		}
	}

	// neg row
	for (int i = 1; i < 8; i++) {
		std::vector<int> newPos = std::vector<int>{ position[0] - i, position[1] };
		if (newPos[0] >= 0) {
			if (playersPositions[newPos[0]][newPos[1]] == player) {
				if (friendlyFire)
					this->moves.push_back(newPos);
				break;
			}
			if (playersPositions[newPos[0]][newPos[1]] == enemy) {
				this->kills.push_back(newPos);
				break;
			}
			this->moves.push_back(newPos);
		}
	}

	// SE
	for (int i = 1; i < 8; i++) {
		std::vector<int> newPos = std::vector<int>{ position[0] + i, position[1] + i };
		if (newPos[0] < 8 && newPos[1] < 8) {
			if (playersPositions[newPos[0]][newPos[1]] == player) {
				if (friendlyFire)
					this->moves.push_back(newPos);
				break;
			}
			if (playersPositions[newPos[0]][newPos[1]] == enemy) {
				this->kills.push_back(newPos);
				break;
			}
			this->moves.push_back(newPos);
		}
	}

	// NE
	for (int i = 1; i < 8; i++) {
		std::vector<int> newPos = std::vector<int>{ position[0] - i, position[1] + i };
		if (newPos[0] >= 0 && newPos[1] < 8) {
			if (playersPositions[newPos[0]][newPos[1]] == player) {
				if (friendlyFire)
					this->moves.push_back(newPos);
				break;
			}
			if (playersPositions[newPos[0]][newPos[1]] == enemy) {
				this->kills.push_back(newPos);
				break;
			}
			this->moves.push_back(newPos);
		}
	}

	// SW
	for (int i = 1; i < 8; i++) {
		std::vector<int> newPos = std::vector<int>{ position[0] + i, position[1] - i };
		if (newPos[0] < 8 && newPos[1] >= 0) {
			if (playersPositions[newPos[0]][newPos[1]] == player) {
				if (friendlyFire)
					this->moves.push_back(newPos);
				break;
			}
			if (playersPositions[newPos[0]][newPos[1]] == enemy) {
				this->kills.push_back(newPos);
				break;
			}
			this->moves.push_back(newPos);
		}
	}

	// NW
	for (int i = 1; i < 8; i++) {
		std::vector<int> newPos = std::vector<int>{ position[0] - i, position[1] - i };
		if (newPos[0] >= 0 && newPos[1] >= 0) {
			if (playersPositions[newPos[0]][newPos[1]] == player) {
				if (friendlyFire)
					this->moves.push_back(newPos);
				break;
			}
			if (playersPositions[newPos[0]][newPos[1]] == enemy) {
				this->kills.push_back(newPos);
				break;
			}
			this->moves.push_back(newPos);
		}
	}
}

char Queen::getDesignation() const {
	return designation;
}

Queen::~Queen() {}
