#ifndef QUEEN_H
#define QUEEN_H

#include "Character.h"
#include<vector>

class Queen : public Character
{
public:
    Queen();
    ~Queen() override;
    //Character*                                  clone() const override { return new Queen(*this); }
    //Queen* getCopy() const override;
    char                                        getDesignation() const override ;
    void                                        checkMoves(std::vector<std::vector<Character*>> board, bool friendlyFire = false, bool checkRescue = true) override ;
};

#endif
