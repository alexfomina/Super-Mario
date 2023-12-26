#include "File_Processor.h"

File_Processor::File_Processor(string input, string output)
{
    //opens the file & reads in all information
    fileToRead = input;
    fileToWrite = output;
    inputFileStream.open(input, ios::in);
    if (inputFileStream.is_open())
    {
        //cout <<" Starting to read" << endl;
        //Read information from the file
        inputFileStream >> levels;
        inputFileStream >> dimensions;
        inputFileStream >> lives;
        inputFileStream >> perCoins;
        inputFileStream >> perNothing;
        inputFileStream >> perGoomba;
        inputFileStream >> perKoopa;
        inputFileStream >> perMushroom;
        inputFileStream.close();
    }
    //opnes file for writing
    inputFileStream.open(fileToWrite, ios::out);

}

File_Processor::~File_Processor(){
    //closes the file
    inputFileStream.close();
}

int File_Processor::getLevels()
{
    return levels;
}
int File_Processor::getDim()
{
    return dimensions;
}
int File_Processor::getLives()
{
    return lives;
}
int File_Processor::getCoins()
{
    return perCoins;
}
int File_Processor::getNothing()
{
    return perNothing;
}
int File_Processor::getGoomba()
{
    return perGoomba;
}
int File_Processor::getKoopa()
{
    return perKoopa;
}
int File_Processor::getMush()
{
    return perMushroom;
}
void File_Processor::write(string s)
{
    //cout << "opening writing" << endl;
    if (inputFileStream.is_open())
    {
        //adds string s to the output file
        inputFileStream << s;
    }
    //cout << "close writing " << endl;
}