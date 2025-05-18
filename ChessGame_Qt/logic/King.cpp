#include "King.h"

King::King() {
	this->points = 1000;
	this->countMoves = 0;
	this->rescueMovesFrom = std::vector<std::vector<int>>();
	this->rescueMovesTo = std::vector<std::vector<int>>();
	DangerZone dangerZone = DangerZone();
}

//King* King::getCopy() const {
//	return new King(*this);
//}

void King::clearMemory() {
	for (int i = 0; i < copy_board.size(); i++) {
		for (int j = 0; j < copy_board[0].size(); j++) {
			if (copy_board[i][j])
				delete this->copy_board[i][j];
			this->copy_board[i][j] = nullptr;
		}
	}
}

// Check for the possible input move if king is still in chess
bool King::rescued(std::vector<std::vector<Character*>> board, int act_row, int act_col, std::vector<int> to) {
	
	board = board[act_row][act_col]->move(board, std::vector<int> { to[0], to[1] });
	board[position[0]][position[1]]->checkMoves(board, false, false);
	
	if (!board[position[0]][position[1]]->isChess()) {
		board = board[position[0]][position[1]]->reverse(board);
		return true;
	}

	board = board[position[0]][position[1]]->reverse(board);
	return false;
}

void King::checkForRescue(std::vector<std::vector<Character*>> board) {
	// TEST
	this->rescueMovesFrom.clear();
	this->rescueMovesTo.clear();
	// TEST

	for (int i = 0; i < board.size(); i++) {
		for (int j = 0; j < board[0].size(); j++) {
			if (board[i][j] == nullptr)
				continue;
			if (board[i][j]->getPlayer() != player || board[i][j]->getPoints() > 10)
				continue;
			
			// TEST
			board[i][j]->checkMoves(board);
			// TEST

			std::vector<std::vector<int>> moves = board[i][j]->getMoves();
			std::vector<std::vector<int>> kills = board[i][j]->getKills();
			moves.insert(moves.end(), kills.begin(), kills.end());
			
			for (int k = 0; k < moves.size(); k++) {
				std::vector<int> pos = std::vector<int>{ i, j };
				bool kingSaved = rescued(board, i, j, moves[k]);
				if (kingSaved) {
					this->rescueMovesFrom.push_back(pos);
					this->rescueMovesTo.push_back(moves[k]);
				}
			}			

			board[i][j]->delMoves();
			board[i][j]->delKills();
		}
	}

	this->chess = true;
}

void King::checkMoves(std::vector<std::vector<Character*>> board, bool friendlyFire, bool checkRescue) {
	this->moves.clear();
	this->kills.clear();
	/*this->rescueMovesFrom.clear();
	this->rescueMovesTo.clear();*/

	dangerZone.createDangerZone(board, player);

	getPlayersPositions(board);
	int enemy = 1;
	if (player == 1)
		enemy = 2;

	std::vector<int> newPos{ position[0], position[1] };

	// Check chess (actual position)
	if (!dangerZone.noChess(newPos)) {
			this->chess = true;
		if (checkRescue)
			checkForRescue(board);
	}		
	else
		this->chess = false;		

	// pos col
	newPos = std::vector<int>{ position[0], position[1] + 1 };
	if (newPos[1] < 8) {
		if (playersPositions[newPos[0]][newPos[1]] == enemy && dangerZone.noChess(newPos))
			this->kills.push_back(newPos);
		else if (playersPositions[newPos[0]][newPos[1]] != player && dangerZone.noChess(newPos))
			this->moves.push_back(newPos);
		else if (playersPositions[newPos[0]][newPos[1]] == player && friendlyFire)
			this->moves.push_back(newPos);
	}

	// neg col
	newPos = std::vector<int>{ position[0], position[1] - 1 };
	if (newPos[1] >= 0) {
		if (playersPositions[newPos[0]][newPos[1]] == enemy && dangerZone.noChess(newPos))
			this->kills.push_back(newPos);
		else if (playersPositions[newPos[0]][newPos[1]] != player && dangerZone.noChess(newPos))
			this->moves.push_back(newPos);
		else if (playersPositions[newPos[0]][newPos[1]] == player && friendlyFire)
			this->moves.push_back(newPos);
	}

	// pos row
	newPos = std::vector<int>{ position[0] + 1, position[1] };
	if (newPos[0] < 8) {
		if (playersPositions[newPos[0]][newPos[1]] == enemy && dangerZone.noChess(newPos))
			this->kills.push_back(newPos);
		else if (playersPositions[newPos[0]][newPos[1]] != player && dangerZone.noChess(newPos))
			this->moves.push_back(newPos);
		else if (playersPositions[newPos[0]][newPos[1]] == player && friendlyFire)
			this->moves.push_back(newPos);
	}

	// neg row
	newPos = std::vector<int>{ position[0] - 1, position[1] };
	if (newPos[0] >= 0) {
		if (playersPositions[newPos[0]][newPos[1]] == enemy && dangerZone.noChess(newPos))
			this->kills.push_back(newPos);
		else if (playersPositions[newPos[0]][newPos[1]] != player && dangerZone.noChess(newPos))
			this->moves.push_back(newPos);
		else if (playersPositions[newPos[0]][newPos[1]] == player && friendlyFire)
			this->moves.push_back(newPos);
	}

	// SE
	newPos = std::vector<int>{ position[0] + 1, position[1] + 1 };
	if (newPos[0] < 8 && newPos[1] < 8) {
		if (playersPositions[newPos[0]][newPos[1]] == enemy && dangerZone.noChess(newPos))
			this->kills.push_back(newPos);
		else if (playersPositions[newPos[0]][newPos[1]] != player && dangerZone.noChess(newPos))
			this->moves.push_back(newPos);
		else if (playersPositions[newPos[0]][newPos[1]] == player && friendlyFire)
			this->moves.push_back(newPos);
	}

	// NE
	newPos = std::vector<int>{ position[0] - 1, position[1] + 1 };
	if (newPos[0] >= 0 && newPos[1] < 8) {
		if (playersPositions[newPos[0]][newPos[1]] == enemy && dangerZone.noChess(newPos))
			this->kills.push_back(newPos);
		else if (playersPositions[newPos[0]][newPos[1]] != player && dangerZone.noChess(newPos))
			this->moves.push_back(newPos);
		else if (playersPositions[newPos[0]][newPos[1]] == player && friendlyFire)
			this->moves.push_back(newPos);
	}

	// SW
	newPos = std::vector<int>{ position[0] + 1, position[1] - 1 };
	if (newPos[0] < 8 && newPos[1] >= 0) {
		if (playersPositions[newPos[0]][newPos[1]] == enemy && dangerZone.noChess(newPos))
			this->kills.push_back(newPos);
		else if (playersPositions[newPos[0]][newPos[1]] != player && dangerZone.noChess(newPos))
			this->moves.push_back(newPos);
		else if (playersPositions[newPos[0]][newPos[1]] == player && friendlyFire)
			this->moves.push_back(newPos);
	}

	// NW
	newPos = std::vector<int>{ position[0] - 1, position[1] - 1 };
	if (newPos[0] >= 0 && newPos[1] >= 0) {
		if (playersPositions[newPos[0]][newPos[1]] == enemy && dangerZone.noChess(newPos))
			this->kills.push_back(newPos);
		else if (playersPositions[newPos[0]][newPos[1]] != player && dangerZone.noChess(newPos))
			this->moves.push_back(newPos);
		else if (playersPositions[newPos[0]][newPos[1]] == player && friendlyFire)
			this->moves.push_back(newPos);
	}

	// Check Rochade
	if (countMoves == 0) {
		// Left
		if (board[position[0]][position[1] - 1] == nullptr && board[position[0]][position[1] - 2] == nullptr && board[position[0]][position[1] - 3] == nullptr && board[position[0]][position[1] - 4]) {
			if (board[position[0]][position[1] - 4]->getDesignation() == 'T' || board[position[0]][position[1] - 4]->getDesignation() == 't' && board[position[0]][position[1] - 4]->numberOfMoves() == 0) {
					std::cout << "Error Rochade" << std::endl;
					this->moves.push_back(std::vector<int>{ position[0], position[1] - 3 });
					std::cout << "No Error Rochade" << std::endl;
			}
		}
		// Right
		if (board[position[0]][position[1] + 1] == nullptr && board[position[0]][position[1] + 2] == nullptr && board[position[0]][position[1] + 3]) {
			if (board[position[0]][position[1] + 3]->numberOfMoves() == 0 && (board[position[0]][position[1] + 3]->getDesignation() == 'T' || board[position[0]][position[1] + 3]->getDesignation() == 't')) {
				std::cout << "Error Rochade" << std::endl;
				this->moves.push_back(std::vector<int>{ position[0], position[1] + 2 });
				std::cout << "No Error Rochade" << std::endl;
			}			
		}
	}
}

std::vector<std::vector<int>> King::getRescueMovesFrom() const {
	return rescueMovesFrom;
}

std::vector<std::vector<int>> King::getRescueMovesTo() const {
	return rescueMovesTo;
}

bool King::isChess() const {
	return chess;
}

char King::getDesignation() const {
	return designation;
}

King::~King() {}
