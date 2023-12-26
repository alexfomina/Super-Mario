#include "Goomba.h"
#include <random>

Goomba::Goomba(){}

Goomba::~Goomba(){}

//returns true or false to indicate whether mario won or lost the fight
bool Goomba::fightResult(){
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<int> diceRoll(0, 100);
        int chance = diceRoll(gen);
        if (chance < 80)
        {
            //Mario wins 80% of the time
            return true;
        }
        else{
            return false;
        }

}