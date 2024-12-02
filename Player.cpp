#include "Player.h"

 
Player::Player(GameMechs* thisGMRef)
{
    mainGameMechsRef = thisGMRef;
    myDir = STOP;

    // more actions to be included
    // playerPos.pos->x = mainGameMechsRef -> getBoardSizeX() / 2;
    // playerPos.pos->y = mainGameMechsRef -> getBoardSizeY() / 2;
    // playerPos.symbol = '@';
    playerPosList = new objPosArrayList();                   //Making space in heap.
    playerPosList->insertHead(objPos(15, 7, '*'));            //Adding an element to the list with the coordinates of the middle of the board.
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
    char input = mainGameMechsRef -> getInput();        //Gets the user input.
    

        // PPA3 input processing logic       
        switch(input)
        {                      
            case 'w':                   //For up
            case 'W':
                if(myDir != DOWN)   //Checks that the direction is not changing by more than 90 degrees
                {
                    myDir = UP;     //Sets the new direction
                }
                break;

            case 'a':
            case 'A':
                if(myDir != RIGHT)         //Checks that the direction is not changing by more than 90 degrees
                {
                    myDir = LEFT;           //Sets the new direction
                }
                break;

            case 's':
            case 'S':
                if(myDir != UP)   //Checks that the direction is not changing by more than 90 degrees
                {
                    myDir = DOWN;   //Sets the new direction
                }
                break;

            
            case 'd':
            case 'D':
                if(myDir != LEFT)   //Checks that the direction is not changing by more than 90 degrees
                {
                    myDir = RIGHT;  //Sets the new direction
                }
                break;

            default:                                             //Default case if no conditions in switch cases are met.
                if(input == 'a'|| input == 'A'){              
                    myDir = LEFT;
                }       
                else if(input == 'd'|| input == 'D'){
                    myDir = RIGHT;
                }                                                    //Determing in what direction to start moving given an input.
                else if(input == 'w'|| input == 'W'){
                    myDir = UP;
                }       
                else if(input == 's' || input == 'S'){
                    myDir = DOWN;
                }
                break;
        }
        input = 0;   //Resets input.
    }

void Player::movePlayer()
{
    // PPA3 Finite State Machine logic
    objPos snakehead;   //Temparory objPos variable.
    snakehead = playerPosList->getHeadElement().getObjPos();         //Setting the variabel to the position of the head element of the list.
    objPos snakeheadCopy = playerPosList->getHeadElement().getObjPos();        //Another variable(copy) also set to the position of the head element of the list.

    switch(myDir){


        case LEFT:                             
            if(snakehead.pos->x == 1){                  //Part of wraparound logic when moving left.
                snakeheadCopy.pos->x = 28;              //When the snakehead is about to hit the border, places it on the far right side.
            }
            else{
                snakeheadCopy.pos->x = --snakehead.pos-> x;    //If not near a border, then make snakeheadcopy a position in front of snakehead.
            }
            
            playerPosList->insertHead(snakeheadCopy);      //Part of moving element. Insert a new element at the head of the list at one position in front of snakehead(snakeheadcopy).
            playerPosList->removeTail();                   //Remove the last element of the list so the snake appears to be moving forward.
            break;

        case RIGHT:
            if(snakehead.pos->x == 28){               //Part of wraparound logic when moving right.
                snakeheadCopy.pos->x = 1;             //When the snakehead is about to hit the border, places it on the far left side.
            }
            else{
                snakeheadCopy.pos->x = ++snakehead.pos-> x;      //If not near a border, then make snakeheadcopy a position in front of snakehead.
            }

            playerPosList->insertHead(snakeheadCopy);           //Part of moving element. Insert a new element at the head of the list at one position in front of snakehead(snakeheadcopy).
            playerPosList->removeTail();                        //Remove the last element of the list so the snake appears to be moving forward.
            break;

        case UP:
            if(snakehead.pos->y == 1){                 //Part of wraparound logic when moving up.
                snakeheadCopy.pos->y = 13;              //When the snakehead is about to hit the border, places it on the far bottom side. 
            }
            else{
                snakeheadCopy.pos->y = --snakehead.pos-> y;         //If not near a border, then make snakeheadcopy a position in front of snakehead.
            }
            
            playerPosList->insertHead(snakeheadCopy);                //Part of moving element. Insert a new element at the head of the list at one position in front of snakehead(snakeheadcopy).
            playerPosList->removeTail();                              //Remove the last element of the list so the snake appears to be moving forward.
            break;
        
        case DOWN:
            if(snakehead.pos->y == 13){               //Part of wraparound logic when moving down.
                snakeheadCopy.pos->y = 1;              //When the snakehead is about to hit the border, places it on the far top side.
            }
            else{
                snakeheadCopy.pos->y = ++snakehead.pos-> y;           //If not near a border, then make snakeheadcopy a position in front of snakehead.
            } 
            
            playerPosList->insertHead(snakeheadCopy);                    //Part of moving element. Insert a new element at the head of the list at one position in front of snakehead(snakeheadcopy).
            playerPosList->removeTail();                                  //Remove the last element of the list so the snake appears to be moving forward.
            break;

        default:
            break;
    }

    if(snakeheadCopy.pos->x == mainGameMechsRef->getFoodPos().pos->x && snakeheadCopy.pos->y == mainGameMechsRef->getFoodPos().pos->y){ //checks if snake has colided with food
        playerPosList->insertHead(snakeheadCopy); //adds a head element without removing the tail in order to make snake grow
        mainGameMechsRef->incrementScore(); // add to score when food is eaten
    }

    
    if(snakeheadCopy.pos -> x > 28){ //Wraparound for when snake crosses right border
        snakeheadCopy.pos -> x = 1; //sets the snake head copy on the other side of the board, this is done for each border in the following if statments
        playerPosList->insertHead(snakeheadCopy); //Sets the player position to the copy position
        playerPosList->removeTail(); //Removes the tail since the player would grow from the addition of the snakehead copy
    }

    if(snakeheadCopy.pos -> x < 1){ //Wraparound for when snake crosses left border
        snakeheadCopy.pos -> x = 28;
        playerPosList->insertHead(snakeheadCopy);
        playerPosList->removeTail();
    }

    if(snakeheadCopy.pos -> y > 13){ //Wraparound for when snake crosses bottom border
        snakeheadCopy.pos -> y = 1;
        playerPosList->insertHead(snakeheadCopy);
        playerPosList->removeTail();
    }
    if(snakeheadCopy.pos -> y < 1){ //Wraparound for when snake crossees top border
        snakeheadCopy.pos -> y = 13;
        playerPosList->insertHead(snakeheadCopy);
        playerPosList->removeTail();
    }        

    for(int i = 2; i < (playerPosList->getSize()); i++){ //Iterates through all of the snake body elements other than the head
        if(snakeheadCopy.pos->x == playerPosList->getElement(i).getObjPos().pos->x && snakeheadCopy.pos->y == playerPosList->getElement(i).getObjPos().pos->y){ //Checks if the snakehead equals any of its body elements
            mainGameMechsRef->setLoseFlag(); //if the snakehead is equal to its body, it sets the lose flag to true indicate the player has lost
            mainGameMechsRef->setExitTrue(); //Once the player loses the game begins it end sequence
        }
    }

}