#ifndef GOOMBA_H
#define GOOMBA_H
#include "Enemy.h"

class Goomba: public Enemy 
{
    public:
    Goomba();
    ~Goomba();
    bool fightResult();

};
#endif