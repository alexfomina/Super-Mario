#include "Game.h"
using namespace std;

int main()
{
    string inputFile;
    cin >> inputFile;
    string outputFile;
    cin >>outputFile;
    Game* myGame = new Game(inputFile, outputFile);
    myGame->play();
    delete myGame;
}