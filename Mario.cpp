#include "Mario.h"

Mario::Mario(int lives)
{
    V = lives;
}

Mario::~Mario()
{
    cout << "Destroyed";
}

//adds coins to mario
void Mario::addCoins()
{
    if (coins == 20)
    {
        coins = 0;
        earnLife();
    }
    coins ++;
    cout << " Mario has " << coins << " coins " << endl;
    
}
string Mario::getCoins()
{
    return to_string(coins);
}
string Mario::getLives()
{
    return to_string(V);
}
bool Mario::getDefeated()
{
    return defeated;
}

//Mario loses a life
void Mario::loseLife()
{
    if (V == 0)
    {
        dead = true;
    }
    else{
        V--;}
    cout << "Mario has " << V << " lives." << endl;
}
void Mario::earnLife()
{
    V++;
    cout << "Mario has: "  << V << " lives. " << endl;
}

//Mario's power level increases, max of 2
void Mario::increasePowerLevel()
{
    if (power_level == 2){
        power_level = 2;
    }
    else{
        power_level++;
    }
    cout << "Current power level: "  <<power_level << endl;
}

//Mario's power level decreases, min of 0
void Mario::decreasePowerLevel()
{
    if (power_level==0){
        power_level = 0;}
    else{
        power_level--;}
    cout << "Current power level: " << power_level << endl;
}
//returns string of mario's current power level
string Mario::getPowerLevel()
{
    return to_string(power_level);
}
//Mario eats a mushroom
//this increases his power level
void Mario::eatMushroom()
{
    increasePowerLevel();
}

//Checks to see if Mario is out of lives
bool Mario::checkDeath()
{
    if (dead)
    {
        return true;
    }
    else{
        return false;
    }
}
//counts how many enemies mario has defeated
void Mario::setEnemiesDefeated()
{
    enemies_defeated = 0;
}

//this is where mario interacts with enemies
//enemy will return a true or false based on whether mario won that fight
bool Mario::fightEnemy(bool b)
{
    //if Mario is at PL0, a life is lost. 
    //he will continue to fight
    if (V == 0)
    {
        dead = true;
    }
    else{
        if (b)
        {
            cout << "Mario won the battle" << endl;
            enemies_defeated++;
            cout << "Mario has defeated " << enemies_defeated << " enemies on this level" << endl;
            defeated = true;
        }
        else 
        {
            if (power_level == 0)
            {
                cout << "Mario is at power level 0! He lost a life. " << endl;
                loseLife();
                defeated = false;
                return false;
            }
            else{
                cout << "Mario's power level was decreased. " << endl;
                decreasePowerLevel();
                defeated = false;
                return true;
            }
        }
    }
}

//Mario's interaction with the boss of each level
bool Mario::fightBoss()
{
    //if Mario is at PL0, a life is lost. 
    //he will continue to fight
    while (V > 0)
    {
        int num = rand() % 2;
        if (num == 0)
        {
            cout << "Mario won the battle" << endl;
            defeated = true;
            return true;
        }
        else{
            if(power_level < 2)
            {
                loseLife();
            }
            else{
                decreasePowerLevel();
                decreasePowerLevel();
            }
            continue;
        }
    }
    return true;
}

