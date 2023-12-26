#include "World.h"
#include <iostream>
#include <algorithm>
#include <random>
#include <chrono>
#include <array>
#include <time.h>
using namespace std;


World::World(int N, int L)
{
    srand (time(NULL));
    X = N;
    Y = N;
    Z = L;

    char myArray[Z][X][Y];
    
    arrPtr = new char**[L];
    for(int i = 0; i < L; ++i){
        arrPtr[i] = new char*[N];
        for (int ii = 0; ii < N; ++ii)
        {
            arrPtr[i][ii] = new char[N];
            for (int iii = 0; iii < N; ++iii){
                arrPtr[i][ii][iii] = 'x';
            }
        }
    }
}
//Do later:
World::~World(){}

//     for (int i = 0; i < Z; ++i )
//     {
//         delete[] arrPtr[i];
//     }
//     delete[] arrPtr;
void World::calculateStatistics(int C, int N, int G, int K, int M)
{
    //Math for the amount of each object in every level
    float num_coins = (C / 100.0) * X * Y;
    numCoins = (int) num_coins;
    float num_nothing = (N/ 100.0) * X * Y;
    numEmpty  = (int) num_nothing;
    float num_goomba = (float) (G / 100.0) * X * Y;
    numGoomba = (int) num_goomba;
    float num_koopa = (float) (K / 100.0) * X * Y;
    numKoopa = (int) num_koopa;
    float num_mushroom = (float) (M / 100.0) * X * Y;
    numMushroom = (int) num_mushroom;

}
string World::returnCurrX()
{
    return to_string(currX);
}
string World::returnCurrY()
{
    return to_string(currY);
}
string World::returnCurrZ()
{
    return to_string(currZ);
}
void World::setClear(bool b)
{
    clear = b;
}
void World::printWorld()
{
    for (int i = 0; i < Z; ++i)
    {
        for (int j =0; j < X; ++j)
        {
            for (int k = 0; k < Y; ++k)
            {
                cout << arrPtr[i][j][k] << " ";
            }
            cout << endl;
        }
        cout << endl;
    }
}
string World::stringWorld()
{
    string ret = "";
    for (int i = 0; i < Z; ++i)
    {
        for (int j =0; j < X; ++j)
        {
            for (int k = 0; k < Y; ++k)
            {
                ret.push_back(arrPtr[i][j][k]);
                ret += " ";
            }
            ret += '\n';
        }
        ret += '\n';
    }
    cout << ret << endl;
    return ret;
}
string World::stringLevel()
{
    string ret = "";
    for (int j =0; j < X; ++j)
        {
            for (int k = 0; k < Y; ++k)
            {
                ret.push_back(arrPtr[currZ][j][k]);
                ret+= " ";
            }
            ret += '\n';
        }
    return ret;
}
void World::printCurrentLevel(int k)
{
    for (int i = 0; i < X; ++i)
    {
        for (int j = 0; j < Y; ++j)
        {
            cout << arrPtr[k][i][j] << " ";
        }
        cout << endl;
    }
}

char* World::generateLevel()
{
    //generates the levels
    char holderArray[X*Y];
    for (int i = 0; i < X*Y; ++i)
    {
        if (i >= 0 && i < numCoins)
        {
            holderArray[i] = 'c';
        }
        else if (i >= numCoins && i < numCoins + numEmpty)
        {
            holderArray[i] = 'x';
        }
        else if (i >= numCoins + numEmpty && i < numCoins + numEmpty + numGoomba)
        {
            holderArray[i] = 'g';
        }
        else if (i >= numCoins + numEmpty + numGoomba && i <= numCoins + numEmpty + numGoomba + numKoopa)
        {
            holderArray[i] = 'k';
        }
        else{
            holderArray[i] = 'm';
        }
    }
    char *ptr = holderArray;
    //Implementing the fisher yates algorithm to randomize the array
    int n = sizeof(holderArray);
    randomize(ptr, n);
    return ptr;
}

void World::generateWorld()
{
    // Every Z should have a unique level based on statistics
    //We have a method that returns a randomized array
    //So, for each Z coordinate, fill the X * Y with this array
    int size = 0;

    for (int i = 0; i < Z; ++i)
    {
        char *levelptr = generateLevel();
        for (int j =0; j < X; ++j)
        {
            for (int k = 0; k < Y; ++k)
            {
                arrPtr[i][j][k] = levelptr[size++];
            }
        }
        size = 0;
        levelptr = nullptr;
    }
    insertPipeAndBoss();
    //Place boss and warp pipe on every level
    // cout << "World has been generated..." << endl;
}
//inserts a pipe and boss into each level
void World::insertPipeAndBoss()
{
    for (int i = 0; i < Z-1; ++i)
    {
        int x = rand() % X;
        int y = rand() % Y;
        int x2 = rand() % X;
        int y2 = rand() % Y;
        char arr[2]= {'W', 'B'};
        char* ptr = arr;
        arrPtr[i][x][y] = ptr[0];
        arrPtr[i][x2][y2] = ptr[1];
    }
    int x = rand() % X;
    int y = rand() % Y;
    arrPtr[Z-1][x][y] = 'B';

}
//Places mario randomly on the map
char World::placeMarioRandomly(int i)
{
    int x = rand() % X;
    int y = rand() % Y;
    char current = arrPtr[i][x][y];
    arrPtr[i][x][y] = 'H';
    currX = x;
    currY = y;
    currZ = i;
    return current;
}
string World::returnCurrDirection()
{
    return currentDirection;
}
//moves Mario up in the level
char World::moveMarioUp()
{
    currentDirection = "Mario moved up \n";
    clearPosition();
    if (currX == 0)
    {
        currX = X-1;
    }
    else{
        --currX;
    }
    char ret = arrPtr[currZ][currX][currY];
    arrPtr[currZ][currX][currY] = 'H';
    return ret;
}
//moves Mario down in the level
char World::moveMarioDown()
{
    currentDirection = "Mario moved down \n";
    clearPosition();
    if (currX == X-1)
    {
        currX = 0;
    }
    else{
        ++currX;
    }
    char ret = arrPtr[currZ][currX][currY];
    arrPtr[currZ][currX][currY] = 'H';
    return ret;
}
//Moves mario to the left in the level
char World::moveMarioLeft()
{
    currentDirection = "Mario moved to the left \n";
    clearPosition();
    
    if (currY == 0)
    {
        currY = Y-1;
    }
    else{
        --currY;
    }
    char ret = arrPtr[currZ][currX][currY];
    arrPtr[currZ][currX][currY] = 'H';
    return ret;

}
//moves mario the right in the level
char World::moveMarioRight()
{
    currentDirection = "Mario moved to the right \n";
    clearPosition();
    if (currY == Y-1)
    {
        currY = 0;
    }
    else{
        ++currY;
    }
    char ret = arrPtr[currZ][currX][currY];
    arrPtr[currZ][currX][currY] = 'H';
    return ret;
}
//replaces character with an x to clear the space
void World::clearPosition()
{
    arrPtr[currZ][currX][currY] = 'x';
}

//returns current x coordinate of Mario
int World::getCurrX()
{
    return currX;
}

//returns current y coordinate of Mario
int World::getCurrY()
{
    return currY;
}
//returns current z coordinate of Mario
int World::getCurrZ()
{
    return currZ;
}

void World::setCurrZ()
{
    if(currZ < Z-1)
    {
        currZ++;
    }
}
int World::generateDirection()
{
    return rand() % 4;
}
bool World::lastLevel()
{
    if (currZ == Z-1)
    {
        return true;
    }
    else{
        return false;
    }
}
void World::setCharInGrid(char c){
    arrPtr[currZ][currX][currY] = c;
}

//moves Mario either up, down, left or right randomly
char World::moveMarioOnGrid(int var)
{
    switch (var)
    {
        case 0:
        {
            return moveMarioUp();
        }
        case 1:
        {
            return moveMarioDown();
        }
        case 2:
        {
            return moveMarioLeft();
        }
        case 3:
        {
            return moveMarioRight();
        }
        default:
            return 'x';
    }
}

//Both methods from this website: https://www.geeksforgeeks.org/shuffle-a-given-array-using-fisher-yates-shuffle-algorithm/
void World::swap(char *a, char *b)
{
    char temp = *a;
    *a = *b;
    *b = temp;
}

void World::randomize(char arr[], int n)
{
    //srand (time(NULL));
    for (int i = n-1; i >0; i--)
    {
        int j = rand() % (i + 1);
        swap(&arr[i], &arr[j]);
    }
}
