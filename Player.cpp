#include "Player.h"


Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;

    // more actions to be included
    playerPos.pos->x = mainGameMechsRef -> getBoardSizeX() / 2;
    playerPos.pos->y = mainGameMechsRef -> getBoardSizeY() / 2;
    playerPos.symbol = '@';
}


Player::~Player()
{
    // delete any heap members here
    // no keyword "new" in the constructor
    // leave the destructor empty FOR NOW
}

objPos Player::getPlayerPos() const
{
    // return the reference to the playerPos arrray list
    return playerPos;
}

void Player::updatePlayerDir()
{
    char input = mainGameMechsRef -> getInput();

        // PPA3 input processing logic   
        switch(input)
        {                      
            case 'w':                   //For up
                if(myDir != DOWN)   //Checks that the direction is not changing by more than 90 degrees
                {
                    myDir = UP;     //Sets the new direction
                }
                break;

            case 'a':
                if(myDir != RIGHT)
                {
                    myDir = LEFT;
                }
                break;

            case 's':
                if(myDir != UP)
                {
                    myDir = DOWN;
                }
                break;
            
            case 'd':
                if(myDir != LEFT)
                {
                    myDir = RIGHT;
                }
                break;
        }
        input = 0;               
}

void Player::movePlayer()
{
    // PPA3 Finite State Machine logic
}

// More methods to be added