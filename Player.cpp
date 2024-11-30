#include "Player.h"

 
Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;

    // more actions to be included
    // playerPos.pos->x = mainGameMechsRef -> getBoardSizeX() / 2;
    // playerPos.pos->y = mainGameMechsRef -> getBoardSizeY() / 2;
    // playerPos.symbol = '@';
    playerPosList = new objPosArrayList();
    playerPosList->insertHead(objPos(15, 7, '*'));
}


Player::~Player()
{
    // delete any heap members here
    // no keyword "new" in the constructor
    // leave the destructor empty FOR NOW
    delete playerPosList;
}

objPosArrayList* Player::getPlayerPos() const
{
    // return the reference to the playerPos arrray list
    return playerPosList;
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

            default:  
                if(input == 'a'){
                    myDir = LEFT;
                }       
                else if(input == 'd'){
                    myDir = RIGHT;
                }
                else if(input == 'w'){
                    myDir = UP;
                }       
                else if(input == 's'){
                    myDir = DOWN;
                }
                break;
        }
        input = 0;
    }

void Player::movePlayer()
{
    // PPA3 Finite State Machine logic
    objPos snakehead;
    snakehead = playerPosList->getHeadElement().getObjPos();
    objPos snakeheadCopy = playerPosList->getHeadElement().getObjPos();

    switch(myDir){


        case LEFT:
            snakeheadCopy.pos->x = --snakehead.pos-> x;
            playerPosList->insertHead(snakeheadCopy);
            playerPosList->removeTail();
            break;

        case RIGHT:
            snakeheadCopy.pos->x = ++snakehead.pos -> x;
            playerPosList->insertHead(snakeheadCopy);
            playerPosList->removeTail();
            break;

        case UP:
            snakeheadCopy.pos->y = --snakehead.pos -> y;
            playerPosList->insertHead(snakeheadCopy);
            playerPosList->removeTail();
            break;
        
        case DOWN:
            snakeheadCopy.pos->y = ++snakehead.pos -> y;
            playerPosList->insertHead(snakeheadCopy);
            playerPosList->removeTail();
            break;

        default:
            break;
    }

    if(snakehead.pos -> x > 28){
        snakehead.pos -> x = 1;
    }

    if(snakehead.pos -> x < 1){
        snakehead.pos -> x = 28;
    }

    if(snakehead.pos -> y > 13){
        snakehead.pos -> y = 1;
    }
    if(snakehead.pos -> y < 1){
        snakehead.pos -> y = 13;
    }        

}

// More methods to be added