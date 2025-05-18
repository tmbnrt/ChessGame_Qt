#ifndef KNIGHT_H
#define KNIGHT_H

#include "Character.h"
#include<vector>

class Knight : public Character
{
public:
    Knight();
    ~Knight() override ;
    //Character*                                  clone() const override { return new Knight(*this); }
    //Knight* getCopy() const override;
    char                                        getDesignation() const override ;
    void                                        checkMoves(std::vector<std::vector<Character*>> board, bool friendlyFire = false, bool checkRescue = true) override ;
};

#endif
