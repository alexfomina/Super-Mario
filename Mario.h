#ifndef MARIO_H
#define MARIO_H
#include <string>
#include <iostream>
using namespace std;
class Mario
{
    public:
        Mario(int lives);
        virtual ~Mario();
        void addCoins();
        void earnLife();
        void loseLife();
        void increasePowerLevel();
        void decreasePowerLevel();
        void eatMushroom();
        bool checkDeath();
        bool fightEnemy(bool b);
        bool fightBoss();
        void interact(char c);
        bool getDefeated();
        string getPowerLevel();
        string getLives();
        string getCoins();
        void setEnemiesDefeated();

    private:
        int V = 0;
        int power_level = 0;
        int coins = 0;
        int enemies_defeated = 0;
        bool dead = false;
        bool defeated = false;


};
#endif