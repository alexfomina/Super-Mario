#ifndef WORLD_H
#define WORLD_H
#include <string>
using namespace std;
class World
{
    public:
        World(int L, int N);
        virtual ~World();
        void printWorld();
        void printCurrentLevel(int k);
        char* generateLevel();
        void generateWorld();
        void swap(char *a, char *b);
        void randomize(char arr[], int n);
        void calculateStatistics(int C, int N, int G, int K, int M);
        void insertPipeAndBoss();
        bool lastLevel();
        char placeMarioRandomly(int i);
        char moveMarioUp();
        char moveMarioDown();
        char moveMarioLeft();
        char moveMarioRight();
        char moveMarioOnGrid(int var);
        void setCurrLocation(int x, int y, int z);
        int getCurrX();
        int getCurrY();
        int getCurrZ();
        string returnCurrX();
        string returnCurrY();
        string returnCurrZ();
        void setCurrZ();
        void setCharInGrid(char c);
        void clearPosition();
        int generateDirection();
        void setClear(bool b);
        string stringWorld();
        string stringLevel();
        string returnCurrDirection();

    private:
        int Z;
        int X;
        int Y;
        int currZ;
        int currX;
        int currY;
        int numMushroom;
        int numEmpty;
        int numKoopa;
        int numGoomba;
        int numCoins;
        char*** arrPtr;
        string currentDirection = "";
        bool clear = true;

};
#endif