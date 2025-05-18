#ifndef PAWN_H
#define PAWN_H

#include "Character.h"
#include<vector>

class Pawn : public Character
{
public:

    Pawn();
    ~Pawn() override ;
    //Character*                                  clone() const override { return new Pawn(*this); }
    //Pawn* getCopy() const override;
    char                                        getDesignation() const override ;
    void                                        checkMoves(std::vector<std::vector<Character*>> board, bool friendlyFire, bool checkRescue = true) override ;
};

#endif
