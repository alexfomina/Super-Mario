#ifndef KOOPA_H
#define KOOPA_H
#include "Enemy.h"

class Koopa : public Enemy{
    public:
    Koopa();
    ~Koopa();

    bool fightResult();

};
#endif