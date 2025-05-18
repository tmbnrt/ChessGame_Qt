#include "Character.h"

#include<iostream>
#include<cstdlib>

Character::Character() {
    this->points = int();
    this->countMoves = int();
    this->designation = char();
    this->player = int();

    std::vector<std::vector<int>> chessZone(8, std::vector<int>(8));
    this->chessZone = chessZone;
}

char Character::getDesignation() const {
	return designation;
}

std::vector<std::vector<int>> Character::getRescueMovesFrom() const {
    return std::vector<std::vector<int>>();
}

std::vector<std::vector<int>> Character::getRescueMovesTo() const {
    return std::vector<std::vector<int>>();
}

void Character::checkMoves(std::vector<std::vector<Character*>> board, bool friendlyFire, bool checkRescue) {}

int Character::getPlayer() const {
    return player;
}

bool Character::isChess() const {
    if (points < 10)
        return false;
}

bool Character::isRescued() const {
    if (points < 10)
        return false;
}

int Character::numberOfMoves() {
    return countMoves;
}

void Character::assign(char c, int p) {
	this->designation = c;
	this->player = p;
}

void Character::defPosition(std::vector<int> pos) {
    this->position = pos;
}

std::vector<int> Character::getPosition() {
    return position;
}

std::vector<std::vector<int>> Character::getMoves() {
    return moves;
}

std::vector<std::vector<int>> Character::getKills() {
    return kills;
}

void Character::delMoves() {
    this->moves.clear();
}

void Character::delKills() {
    this->kills.clear();
}

void Character::getPlayersPositions(std::vector<std::vector<Character*>> board) {
    bool print = false;
    std::vector<std::vector<int>> field(8, std::vector<int>(8));
    this->playersPositions = field;

    for (int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board[0].size(); j++) {
            if (board[i][j] != nullptr)
                this->playersPositions[i][j] = board[i][j]->getPlayer();
            else
                this->playersPositions[i][j] = 0;

            if (print)
                std::cout << " " << playersPositions[i][j] << " ";
        }
        if (print)
            std::cout << std::endl;
    }
    if (print)
        std::cout << std::endl;
}

void Character::store_lastKill(Character* character) {
    this->lastMove_Killed = character;
}

void Character::store_lastMove(std::vector<int> from, std::vector<int> to) {
    this->lastMove_From = from;
    this->lastMove_To = to;
}

std::vector<std::vector<Character*>> Character::move(std::vector<std::vector<Character*>> board, std::vector<int> target, bool testMove) {
    // Save move for reverse case
    for (int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board[0].size(); j++) {
            if (!board[i][j])
                continue;

            if (board[i][j]->getPlayer() == player) {
                // Check En Passante
                if (getPoints() == 1 && board[target[0]][target[1]] == nullptr && position[0] != target[0]) {
                    if (player == 1 && (target[0] - 1) >= 0) {
                        if (board[target[0] - 1][target[1]]) {
                            if (board[target[0] - 1][target[1]]->getPoints() == 1) {
                                board[i][j]->store_lastKill(board[target[0] - 1][target[1]]);
                                board[i][j]->store_lastMove(position, target);
                                continue;
                            }
                        }
                    }                    
                    else if (player == 2 && (target[0] + 1) < 8) {
                        if (board[target[0] + 1][target[1]]) {
                            if (board[target[0] + 1][target[1]]->getPoints() == 1) {
                                board[i][j]->store_lastKill(board[target[0] + 1][target[1]]);
                                board[i][j]->store_lastMove(position, target);
                                continue;
                            }
                        }                        
                    }
                }

                if (board[target[0]][target[1]])
                    board[i][j]->store_lastKill(board[target[0]][target[1]]);
                else
                    board[i][j]->store_lastKill(nullptr);
                board[i][j]->store_lastMove(position, target);
            }
        }
    }

    // En Passant -> kill enemy    
    if (points == 1 && board[target[0]][target[1]] == nullptr && position[1] != target[1]) {
        if (player == 1)
            board[target[0] + 1][target[1]] = nullptr;
        else
            board[target[0] - 1][target[1]] = nullptr;
    }    

    // Check Rochade -> move rook
    if (points > 100 && std::abs(position[1] - target[1]) > 1 && !testMove) {
        if (target[1] == 1) {
            board[position[0]][2] = board[position[0]][0];
            board[position[0]][0] = nullptr;
            board[position[0]][2]->defPosition(std::vector<int>{position[0], 2});
        }
        if (target[1] == 6) {
            board[position[0]][5] = board[position[0]][7];
            board[position[0]][7] = nullptr;
            board[position[0]][5]->defPosition(std::vector<int>{position[0], 5});
        }
    }
    
    // Copy figure on board and delete reference figure
    board[target[0]][target[1]] = board[position[0]][position[1]];
    board[position[0]][position[1]] = nullptr;
    this->position = target;
    this->countMoves++;

    return board;
}

std::vector<std::vector<Character*>> Character::reverse(std::vector<std::vector<Character*>> board) {
    // Copy figure on board and delete reference figure
    board[lastMove_From[0]][lastMove_From[1]] = board[lastMove_To[0]][lastMove_To[1]];
    if (lastMove_Killed) {
        //board[lastMove_To[0]][lastMove_To[1]] = lastMove_Killed;
        std::vector<int> oldPos = lastMove_Killed->getPosition();
        board[oldPos[0]][oldPos[1]] = lastMove_Killed;
    }        
    else
        board[lastMove_To[0]][lastMove_To[1]] = nullptr;
    board[lastMove_From[0]][lastMove_From[1]]->defPosition(lastMove_From);
    this->countMoves--;

    return board;
}

int Character::getPoints() {
    return points;
}

Character::~Character() {}
