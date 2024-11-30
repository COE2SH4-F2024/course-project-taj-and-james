#include "GameMechs.h"
#include "MacUILib.h"
 
GameMechs::GameMechs()
{
    input = 0;
    exitFlag = false;
    loseFlag = false;
    score = 0;

    boardSizeX = 30;
    boardSizeY = 15;    
}

GameMechs::GameMechs(int boardX, int boardY)
{
    input = 0;
    exitFlag = false;
    loseFlag = false;
    score = 0;

    boardSizeX = boardX;
    boardSizeY = boardY;   
}

// Copy COnstructor

// Copy Assignment Operatoer

// do you need a destructor?
GameMechs::~GameMechs()
{
    
}

bool GameMechs::getExitFlagStatus() const
{
    return exitFlag;        //1B
}

bool GameMechs::getLoseFlagStatus() const
{
    return loseFlag;   //1B
}
    

char GameMechs::getInput()
{
    if(MacUILib_hasChar())              // Detects an input
    {
       input = MacUILib_getChar();      // Records input
    }
    return input;
}

int GameMechs::getScore() const
{
    return score;
}

void GameMechs::incrementScore()
{
    score++;
}

int GameMechs::getBoardSizeX() const
{
    return boardSizeX;
}

int GameMechs::getBoardSizeY() const
{
    return boardSizeY;
}


void GameMechs::setExitTrue()
{
    exitFlag = true;        // Did it cause i think its right 
}

void GameMechs::setLoseFlag()
{
    loseFlag = true;   // Did it cause i think its right 
}

void GameMechs::setInput(char this_input)
{
    this_input = input;   // I THINK THIS IS RIGHT IDK?
}

void GameMechs::clearInput()
{
    input = 0;    // ALSO THINK ITS RIGHT
}

// More methods should be added here

void GameMechs::generateFood(objPosArrayList* blockOff)
{
    srand(time(NULL)); //seeds random number generator with current time

    int x, y, i, flag = 0;

    x = (rand() % (boardSizeX-2)+1);
    y = (rand() % (boardSizeY-2)+1);

    for(i = 0; i < blockOff->getSize(); i++)
        if(x==(blockOff->getElement(i).getObjPos().pos->x) && y==(blockOff->getElement(i).getObjPos().pos->y))
        {
            generateFood(blockOff);    // JAMES FAULT IF IT DOESNT WORK
            flag = 1;
        }
    
    if(flag!=1){
        foodPos.pos->x = x;
        foodPos.pos->y = y;  
    }
      

    foodPos.symbol = '+';
}

objPos GameMechs::getFoodPos()
{
    return foodPos;
}