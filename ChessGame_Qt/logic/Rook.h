#ifndef ROOK_H
#define ROOK_H

#include "Character.h"

#include<vector>

class Rook : public Character
{
public:
    Rook();
    ~Rook() override;
    //Character*                                  clone() const override { return new Rook(*this); }
    //Rook* getCopy() const override;
    char                                        getDesignation() const override ;
    void                                        checkMoves(std::vector<std::vector<Character*>> board, bool friendlyFire = false, bool checkRescue = true) override ;
};

#endif
