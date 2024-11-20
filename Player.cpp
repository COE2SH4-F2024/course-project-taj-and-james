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
    Player*myPlayer;
    objPos playerPos = myPlayer -> getPlayerPos();

    switch(myDir){
        case LEFT:
            playerPos.pos -> x --;
            break;

        case RIGHT:
            playerPos.pos -> x ++;
            break;

        case UP:
            playerPos.pos -> y--;
            break;
        
        case DOWN:
            playerPos.pos -> y++;
            break;

        default:
            break;
    }

    if(playerPos.pos -> x > 18){
        playerPos.pos -> x = 1;
    }

    if(playerPos.pos -> x < 1){
        playerPos.pos -> x = 18;
    }

    if(playerPos.pos -> y > 8){
        playerPos.pos -> y = 1;
    }
    if(playerPos.pos -> y < 1){
        playerPos.pos -> y = 8;
    }             
}

// More methods to be added