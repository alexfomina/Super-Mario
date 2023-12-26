#ifndef GAME_H
#define GAME_H
#include "Mario.h"
#include "World.h"
#include "Koopa.h"
#include "Goomba.h"
#include "File_Processor.h"
#include <string>
#include <iostream>
class Game{
    public:
        Game(int V, int N, int L, int C, int E, int G, int K, int M);
        Game(string s, string q);
        virtual ~Game();
        int interact(char c);
        char placeMario(int i);
        void printScreen(int k);
        string printWorld();
        string printLevel();
        string currentInformation();
        char moveMario(int i);
        void play();
        bool endGame();
    private:
        Mario* myHero;
        World* myWorld;
        Goomba* goomba;
        Koopa* koopa;
        File_Processor* myFile;
        int currentLevel = 0;
        int maxLevel;
        bool lastBossDefeated;
        string finalEnding;

};
#endif