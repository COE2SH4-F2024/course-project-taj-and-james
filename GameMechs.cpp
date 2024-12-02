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

GameMechs::GameMechs(const GameMechs &copy){
    input = 0;
    exitFlag = false;
    loseFlag = false;
    score = 0;
    
    boardSizeX = copy.boardSizeX;
    boardSizeY = copy.boardSizeY;
}

GameMechs& GameMechs::operator=(const GameMechs &copy){
     if(this != &copy){
        input = 0;
        exitFlag = false;
        loseFlag = false;
        score = 0;
        this->boardSizeX = copy.boardSizeX;
        this->boardSizeY = copy.boardSizeY;
     }
     return *this;
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
    exitFlag = true; 
}

void GameMechs::setLoseFlag()
{
    loseFlag = true;  
}

void GameMechs::setInput(char this_input)
{
    input = this_input;
}

void GameMechs::clearInput()
{
    input = 0;
}

// More methods should be added here

void GameMechs::generateFood(objPosArrayList* blockOff) //blockOff is the player position
{
    srand(time(NULL)); //seeds random number generator with current time

    int x, y, i, flag = 0; // x and y are temporary variables to store randomly generated coordinates, flag checks if the generated values have been assigned to the position of the food

    x = (rand() % (boardSizeX-2)+1);// generates random x and y coordinates on the game board
    y = (rand() % (boardSizeY-2)+1);

    for(i = 0; i < blockOff->getSize(); i++)
        if(x==(blockOff->getElement(i).getObjPos().pos->x) && y==(blockOff->getElement(i).getObjPos().pos->y)) //Checks if the food has been generated where the player is
        {
            generateFood(blockOff); //Re-runs the generateFood function
            flag = 1; //Marks that the food position should not be updated with the values which match the player position
        }
    
    if(flag!=1){
        foodPos.pos->x = x;//Updates the food position only if it doesn't match the player position
        foodPos.pos->y = y;  
    }
      

    foodPos.symbol = '+';
}

objPos GameMechs::getFoodPos()
{
    return foodPos;
}