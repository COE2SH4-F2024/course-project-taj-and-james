#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
 
#include "Player.h"

using namespace std;

#define DELAY_CONST 100000

Player *myPlayer; //Global pointer meant to instantiate a player object on the heap
GameMechs *myGM;  //Global pointer meant to instantiate the Game Mechanics on the heap

void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);

int main(void)
{

    Initialize();

    while(myGM ->getExitFlagStatus() == false)  
    {
        GetInput();
        RunLogic();
        DrawScreen();
        LoopDelay();
    }

    CleanUp();

}


void Initialize(void)
{
    MacUILib_init();
    MacUILib_clearScreen();

    
    myGM = new GameMechs(); //alocates memory to the game mechs object
    myPlayer = new Player(myGM);    //alocates memory to the player object
    
    objPosArrayList* playerPosList = myPlayer->getPlayerPos(); //create a pointer to the player position list
 
    myGM->generateFood(playerPosList); //generates the first food object

}

void GetInput(void) //Gets user input
{
    myGM->getInput();
}

void RunLogic(void)
{
    myPlayer->updatePlayerDir();    //Updates the player direction
    myPlayer->movePlayer();         //Moves the player
    // MacUILib_printf("hello");
    objPosArrayList* playerPosList = myPlayer -> getPlayerPos(); //Gets access to the playerPoList location pointer
    objPos food = myGM->getFoodPos();                            //Gets access to the food position

    if(myGM->getInput() == 27){     //Checks if user has pressed escape to close the program
        myGM -> setExitTrue();
    }

    if(playerPosList->getHeadElement().pos->x == food.pos->x && playerPosList->getHeadElement().pos->y == food.pos->y) //Checks if the player has eaten the food
    {
        myGM -> generateFood(playerPosList); //Generates food if the player eats the food
    }

}


void DrawScreen(void)
{
    MacUILib_clearScreen();  
    
    objPosArrayList* playerPosList = myPlayer -> getPlayerPos(); //Gets pointer to player position head
    objPos food = myGM->getFoodPos(); //Gets food position

    for (int j = 0; j < myGM->getBoardSizeY(); j++) { // Iterates through all of the rows of the board
        for(int i = 0; i < myGM->getBoardSizeX(); i++) { // Iterates through all of the collumns of the board
            int printed = 0; //Flag to check if either player, food, or border has been printed
            for(int k = 0; k < playerPosList->getSize();k++)
            {
                if(i==(playerPosList->getElement(k).getObjPos().pos->x) && j==(playerPosList->getElement(k).getObjPos().pos->y)){ //looks for player position
                    MacUILib_printf("%c", playerPosList->getElement(k).symbol);
                    printed = 1;
                    break; //Exits the for loop if the player position is found
                }
            }

            if(printed != 1 && food.pos -> x == i && food.pos -> y == j){ //looks for the food
                MacUILib_printf("%c", food.symbol); //prints food once found
                printed = 1;
            }    
            else if((j == 0 || j == 14 || i == 0 || i == 29) && printed != 1) {
                MacUILib_printf("#");   //prints borders
                printed = 1;
            } 
            else if(printed != 1){ //prints blank space if either player, food, or border is not printed
                MacUILib_printf(" "); 
            }
             
        }
        MacUILib_printf("\n");  
     }
    MacUILib_printf("\nScore: %d", myGM->getScore());
    
    if(myGM->getExitFlagStatus() == true && myGM->getLoseFlagStatus() == false){ //Checks if the exit flag has been called and that the player hasn't lost
        MacUILib_printf("\nYOU EXITED THE GAME"); //Prints the exit message
    }
    if(myGM->getExitFlagStatus() == true && myGM->getLoseFlagStatus() == true){ //Checks if the exit flag has been called and that the player has lost
        MacUILib_printf("\nYOU LOSE! TRY AGAIN NEXT TIME"); //Prints the lose message
    }
}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{    

    delete myPlayer;  //deletes the memory allocated for the player
    delete myGM;      //deletes memory allocated for game mechanics as a precaution
    MacUILib_uninit(); 
}
