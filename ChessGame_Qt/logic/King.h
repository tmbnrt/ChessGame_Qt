#ifndef KING_H
#define KING_H

#include "Character.h"
//#include "Player.h"
#include<vector>
#include<iostream>

class King : public Character
{
public:
    King();
    ~King() override ;
    //Character*                                  clone() const override { return new King(*this); }
    //King* getCopy() const override;
    char                                        getDesignation() const override ;
    void                                        checkMoves(std::vector<std::vector<Character*>> board, bool friendlyFire = false, bool checkRescue = true) override ;
    bool                                        isChess() const override ;
    std::vector<std::vector<int>>               getRescueMovesFrom() const override ;
    std::vector<std::vector<int>>               getRescueMovesTo() const override ;

private:
    void                                        checkForRescue(std::vector<std::vector<Character*>> board);
    DangerZone									dangerZone;
    bool                                        chess;
    std::vector<std::vector<int>>               rescueMovesFrom;
    std::vector<std::vector<int>>               rescueMovesTo;
    std::vector<std::vector<Character*>>        copy_board;
    bool                                        rescued(std::vector<std::vector<Character*>> board, int act_row, int act_col, std::vector<int> to);
    void                                        clearMemory();
    std::vector<std::vector<Character*>>        copyBoard(std::vector<std::vector<Character*>> input);
    //Player                                      copyPlayer_white;
    //Player                                      copyPlayer_black;
};

#endif
