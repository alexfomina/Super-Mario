#ifndef FILE_PROCESSOR_H
#define FILE_PROCESSOR_H
//#include "Game.h"
#include <string>
#include <fstream>
#include <iostream>
using namespace std;
class File_Processor{
    public:
        File_Processor(string fileName, string outputFile);
        virtual ~File_Processor();
        void write(string s);
        int getLevels();
        int getDim();
        int getLives();
        int getCoins();
        int getNothing();
        int getGoomba();
        int getKoopa();
        int getMush();
    private:

        fstream inputFileStream;
        string fileToRead;
        string fileToWrite;
        int levels;
        int dimensions;
        int lives;
        int perCoins;
        int perNothing;
        int perGoomba;
        int perKoopa;
        int perMushroom;
};
#endif