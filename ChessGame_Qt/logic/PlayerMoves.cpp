#include "PlayerMoves.h"

PlayerMoves::PlayerMoves() {
	this->from = std::vector<std::vector<int>>();
	this->to = std::vector<std::vector<int>>();
	this->history_from = std::vector<std::vector<int>>();
	this->history_to = std::vector<std::vector<int>>();
	this->chess = false;
}

void PlayerMoves::addHistory(std::vector<int> actual, std::vector<int> target) {
	this->history_from.push_back(actual);
	this->history_to.push_back(target);
}

bool PlayerMoves::isSuizide(std::vector<std::vector<Character*>> board, int player, std::vector<int> actual, std::vector<int> target) {
	// Find own king
	std::vector<int> kingPos;
	for (int i = 0; i < board.size(); i++)
		for (int j = 0; j < board[0].size(); j++)
			if (board[i][j])
				if (board[i][j]->getPlayer() == player && board[i][j]->getPoints() > 10)
					kingPos = std::vector<int>{ i, j };

	// Test move and check for suizide
	board = board[actual[0]][actual[1]]->move(board, target);
	if (kingPos[0] == actual[0] && kingPos[1] == actual[1]) {		
		board[target[0]][target[1]]->checkMoves(board, false, false);
		if (board[target[0]][target[1]]->isChess()) {
			board = board[target[0]][target[1]]->reverse(board);
			return true;
		}

		board = board[target[0]][target[1]]->reverse(board);

		return false;
	}
	else {
		board[kingPos[0]][kingPos[1]]->checkMoves(board, false, false);
		if (board[kingPos[0]][kingPos[1]]->isChess()) {
			board = board[target[0]][target[1]]->reverse(board);
			return true;
		}

		board = board[target[0]][target[1]]->reverse(board);

		return false;
	}
	
	return false;
}

void PlayerMoves::checkPlayerMoves(std::vector<std::vector<Character*>> board, int player) {
	// del former possibilities
	this->from.clear();
	this->to.clear();

	this->chess = false;

	// Get new possibilities
	for (int i = 0; i < board.size(); i++) {
		for (int j = 0; j < board[0].size(); j++) {
			if (board[i][j] != nullptr) {
				if (board[i][j]->getPlayer() == player) {
					board[i][j]->checkMoves(board);

					std::vector<int> actual = std::vector<int>{ i, j };
					std::vector<std::vector<int>> targets = board[i][j]->getMoves();
					std::vector<std::vector<int>> kills = board[i][j]->getKills();
					targets.insert(targets.end(), kills.begin(), kills.end());
					
					if (board[i][j]->isChess()) {
						this->chess = true;
						this->from.clear();
						this->to.clear();
						this->from = board[i][j]->getRescueMovesFrom();
						this->to = board[i][j]->getRescueMovesTo();
						std::cout << "In chess: Player " + player << std::endl;
					}

					for (int k = 0; k < targets.size(); k++) {
						if (isSuizide(board, player, actual, targets[k]))
							continue;

						this->from.push_back(actual);
						this->to.push_back(targets[k]);
					}

					if (chess)
						break;
				}				
			}			
		}

		if (chess)
			break;
	}
}

bool PlayerMoves::checkAllowedActual(std::vector<int> actual) {
	for (int i = 0; i < from.size(); i++)
		if (from[i][0] == actual[0] && from[i][1] == actual[1])
			return true;

	return false;
}

bool PlayerMoves::checkAllowedTarget(std::vector<int> target) {
	for (int i = 0; i < from.size(); i++)
		if (to[i][0] == target[0] && to[i][1] == target[1])
			return true;

	return false;
}

bool PlayerMoves::checkAllowed(std::vector<int> actual, std::vector<int> target) {
	for (int i = 0; i < from.size(); i++)
		if (from[i][0] == actual[0] && from[i][1] == actual[1] && to[i][0] == target[0] && to[i][1] == target[1])
			return true;
	
	return false;
}

std::vector<std::vector<int>> PlayerMoves::getTargets(std::vector<int> actual) {
	std::vector<std::vector<int>> targets;
	for (int i = 0; i < from.size(); i++)
		if (from[i][0] == actual[0] && from[i][1] == actual[1])
			targets.push_back(to[i]);

	return targets;
}

int PlayerMoves::getNumberMoves() {
	return from.size();
}

std::vector<int> PlayerMoves::getRandFrom(int act) {
	return from[act];
}

std::vector<int> PlayerMoves::getRandTarget(int act) {
	return to[act];
}

bool PlayerMoves::isChess() const {
	return chess;
}

bool PlayerMoves::checkMate() {
	if (chess)
		if (from.size() == 0 && to.size() == 0)
			return true;

	return false;
}

void PlayerMoves::clear() {
	this->from.clear();
	this->to.clear();
}

PlayerMoves::~PlayerMoves(){}