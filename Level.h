#ifndef LEVEL_H
#define LEVEL_H
#include <iostream>
using namespace std;
class Level{
    public:
        Level(int N);
        virtual ~Level();
        void printLevel();
    private:
        int size;
        char** arrPtr;

};
#endif