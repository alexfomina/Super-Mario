#include "Koopa.h"
#include <random>

Koopa::Koopa()
{}

Koopa::~Koopa(){}
//returns true or false based on whether mario defeated the koopa
bool Koopa::fightResult(){
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<int> diceRoll(0, 100);
        int chance = diceRoll(gen);
        if (chance < 65)
        {
            //Mario wins 65% of the time
            return true;
        }
        else{
            return false;
        }

    }