#include "Game.h"
using namespace std;

Game::Game(int V, int N, int L, int C, int E, int G, int K, int M)
{
    //default constructor
    cout << "The game has started!" << endl;
    //initializes mario with V lives
    myHero = new Mario(V);
    //Creates a world with L levels and N * N dimensions
    myWorld = new World(N, L);
    //creates a koopa
    koopa = new Koopa();
    //creates a goomba
    goomba = new Goomba();
    maxLevel = L;
    //calculates percentage of each object
    myWorld->calculateStatistics(C, E, G, K, M);
    myWorld->generateWorld();
    myFile->write("------------------------------------------------- \n");
    myFile->write(myWorld->stringWorld());
    myWorld->printWorld();

}
Game::Game(string input, string output)
{
    //Game method takes in string name of input & output file
    //File constructor opens txt file and reads in information
    myFile = new File_Processor(input, output);
    cout << "Starting game..." << endl;
    //Initializing objects w/ info read by myFile
    myHero = new Mario(myFile->getLives());
    myWorld = new World(myFile->getDim(), myFile->getLevels());
    koopa = new Koopa();
    goomba = new Goomba();
    maxLevel = myFile->getLevels();
    //World is created w info from myFile
    myWorld->calculateStatistics(myFile->getCoins(), myFile->getNothing(), myFile->getGoomba(), myFile->getKoopa(), myFile->getMush());
    myWorld->printWorld();
    myWorld->generateWorld();
    //Adds a string interpretation of the current world (all levels) and writes it to export file
    myFile->write(myWorld->stringWorld());
    myWorld->printWorld();
}
Game::~Game()
{
    delete myHero;
    delete myWorld;
    delete koopa;
    delete goomba;
    delete myFile;
}

int Game::interact(char c)
{
    //method where mario interacts w/ the world based on the character
    cout << "we are going to interact" << endl;
    switch (c)
    {
        case 'm':
        {
            //Mario will eat the mushroom, and the position will clear
            string mushroom = "Mario ate a mushroom \n";
            myFile->write(mushroom);
            myHero->eatMushroom();
            myWorld->clearPosition();
            myWorld->setClear(true);
            return myWorld->generateDirection();
        }
        case 'c':
        {
            //Mario will gain a coin and the position will clear
            string coin = "Mario got a coin \n";
            myFile->write(coin);
            myHero->addCoins();
            myWorld->clearPosition();
            myWorld->setClear(true);
            return myWorld->generateDirection();
        }
        case 'g':
        {
            //Mario will attempt to fight the goomba
            string Goomba = "Mario is fighting a goomba and won (";
            myFile->write(Goomba);
            bool fightResult = goomba->fightResult();
            myFile->write(to_string(fightResult));
            myFile->write(") \n");
            bool b = myHero->fightEnemy(fightResult);
            while (b == false)
            {
                string Goomba = "Mario is fighting a goomba again and won (";
                myFile->write(Goomba);
                fightResult = goomba->fightResult();
                myFile->write(to_string(fightResult));
                myFile->write(") \n");
                b = myHero->fightEnemy(fightResult);
            }
            myWorld->setClear(myHero->getDefeated());
            return myWorld->generateDirection();
        }
        case 'k':
        {
            //Mario will attempt to fight the koopa
            string K = "Mario is fighting a Koopa and won (";
            myFile->write(K);
            bool fight = koopa->fightResult();
            myFile->write(to_string(fight));
            myFile->write(") \n");
            cout << "fight result " << fight << endl;
            bool b = myHero->fightEnemy(fight);
            while (b == false)
            {
                string K = "Mario is fighting a Koopa again and won (";
                myFile->write(K);
                fight = koopa->fightResult();
                myFile->write(to_string(fight));
                myFile->write(") \n");
                b = myHero->fightEnemy(fight);
            }
            myWorld->setClear(myHero->getDefeated());
            return myWorld->generateDirection();
        }
        case 'x':
        {
            //Mario will move on
            string message = "The position is empty \n";
            myFile->write(message);
            myWorld->setClear(true);
            return myWorld->generateDirection();
        }
        case 'B':
        {
            // Mari owill atempt to fight the boss of the level
            string boss = "Mario is fighting the boss! ";
            bool b = myHero->fightBoss();
            boss += " Mario beat the boss: " + to_string(b) + "\n";
            myFile->write(boss);
            //Mario needs to fight the boss until he dies or beats him

            while (!b)
            {
                b = myHero->fightBoss();
                boss = "Mario is fighting the boss again! ";
                boss += " Mario beat the boss: " + to_string(b) + "\n";
                myFile->write(boss);
            }
            myWorld->setClear(true);
            if(myWorld->getCurrZ() == maxLevel-1)
            {
                lastBossDefeated = true;
            }
            myWorld->setCurrZ();
            myHero->setEnemiesDefeated();
            myWorld->placeMarioRandomly(myWorld->getCurrZ());
            return myWorld->generateDirection();
        }
        case 'W':
        {
            string warp = "Mario is warping... \n";
            myFile->write(warp);
            //current Z is incremented
            //Mario is randomly generated on the next level
            myWorld->setClear(true);
            myWorld->setCurrZ();
            myHero->setEnemiesDefeated();
            myWorld->placeMarioRandomly(myWorld->getCurrZ());
            return myWorld->generateDirection();
        }
        default:
            cout << "UH OH DEFAULT CASE " << endl;
            return -1;
    }
}
//prints current level
void Game::printScreen(int k){
    myWorld->printCurrentLevel(k);
}
//returns a string with the current information about game play
string Game::currentInformation()
{
    cout << "retrieving current information" << endl;
    string ret = "";
    ret += "Level: " + myWorld->returnCurrZ() + "\n";
    ret += "Current Location: (" + myWorld->returnCurrX() + "," + myWorld->returnCurrY() + ")" + "\n";
    ret += "Current Power Level: " + myHero->getPowerLevel() + "\n";
    ret += "Mario has: " + myHero->getCoins() + " coins.  \n";
    ret += "Mario has: " + myHero->getLives() + " lives left \n";
    return ret;
}
//Checks to see if the game should end
//game ends when Mario is out of lives or when he defeats the last boss
bool Game::endGame(){
    if (myHero->checkDeath() == true)
    {
        finalEnding = "Mario did not win the game :( \n";
        return true;
    }
    else if (lastBossDefeated)
    {
        finalEnding = "Mario won the game! \n";
        return true;
    }
    return false;
}
//Returns a string representation of the world
string Game::printWorld()
{
    return myWorld->stringWorld();
}
//Returns a string representation of the current level
string Game::printLevel()
{
    return myWorld->stringLevel();
}
//Places mario randomly on a level
char Game::placeMario(int i)
{
    return myWorld->placeMarioRandomly(i);
}
//returns a char representation of where Mario moved onto the grid
char Game::moveMario(int i)
{
    return myWorld->moveMarioOnGrid(i);
}
void Game::play()
{
    //Main function where the actual game play takes place
    cout << "entering the play function" << endl;
    //game starts with Mario getting randomly generated on a square
    //Mario needs to interact with the square!
    printWorld();
    myFile->write(printLevel());
    char currentChar = placeMario(0);
    myFile->write(currentInformation());
    int w = 0;
    while ( !(endGame()) )
    {
            int n = interact(currentChar);
            //File will get written what happened inside the interact function
            currentChar = moveMario(n);
            //Need to write what direction mario moved
            myFile->write(myWorld->returnCurrDirection());
            //Then, print the new level he is on
            myFile->write(printLevel());
            //then, print currentInfo about this level.
            myFile->write(currentInformation());
            // cout << "screen after moving " << endl;
            // printScreen(myWorld->getCurrZ());
            w++;
    }
    myFile->write(finalEnding);
    myFile->write("Mario took a total of " + to_string(w) + " steps.");
    cout << "Ending simulation" << endl;
}
// int main()
// {
//     Game* myGame = new Game(3, 4, 3, 20, 20, 20, 20, 20);
//     myGame->play();
// }

