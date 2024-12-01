#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
 
#include "Player.h"

using namespace std;

#define DELAY_CONST 100000

Player *myPlayer; //Global pointer meant to instantiate a player object on the heap
GameMechs *myGM;

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

    
    myGM = new GameMechs();
    myPlayer = new Player(myGM);
    
    objPosArrayList* playerPosList = myPlayer->getPlayerPos();

    myGM->generateFood(playerPosList);

}

void GetInput(void)
{
    myGM->getInput();
}

void RunLogic(void)
{
    myPlayer->updatePlayerDir();
    myPlayer->movePlayer();
    // MacUILib_printf("hello");
    objPosArrayList* playerPosList = myPlayer -> getPlayerPos();
    objPos food = myGM->getFoodPos();

    if(myGM->getInput() == 27){
        myGM -> setExitTrue();
    }

    if(playerPosList->getHeadElement().pos->x == food.pos->x && playerPosList->getHeadElement().pos->y == food.pos->y)
    {
        myGM -> generateFood(playerPosList);
    }

}

//comment to pull

void DrawScreen(void)
{
    MacUILib_clearScreen();  
    
    objPosArrayList* playerPosList = myPlayer -> getPlayerPos();
    objPos food = myGM->getFoodPos(); 

    for (int j = 0; j < myGM->getBoardSizeY(); j++) {
        for(int i = 0; i < myGM->getBoardSizeX(); i++) {
            int printed = 0;
            for(int k = 0; k < playerPosList->getSize();k++)
            {
                if(i==(playerPosList->getElement(k).getObjPos().pos->x) && j==(playerPosList->getElement(k).getObjPos().pos->y)){
                    MacUILib_printf("%c", playerPosList->getElement(k).symbol);
                    printed = 1;
                    break;
                    
                }
            }

            if(printed != 1 && food.pos -> x == i && food.pos -> y == j){
                MacUILib_printf("%c", food.symbol);
                printed = 1;
            }    
            else if((j == 0 || j == 14 || i == 0 || i == 29) && printed != 1) {
                MacUILib_printf("#");  
                printed = 1;
            } 
            else if(printed != 1){
                MacUILib_printf(" "); 
            }
             
        }
        MacUILib_printf("\n");  
     }
    MacUILib_printf("\nScore: %d", myGM->getScore());
    
    if(myGM->getExitFlagStatus() == true && myGM->getLoseFlagStatus() == false){
        MacUILib_printf("\nYOU EXITED THE GAME");
    }
    if(myGM->getExitFlagStatus() == true && myGM->getLoseFlagStatus() == true){
        MacUILib_printf("\nYOU LOSE! TRY AGAIN NEXT TIME");
    }

    // MacUILib_printf("Player [x, y, sym] = [%d, %d, %c]\n", playerPos.pos -> x, playerPos.pos -> y, playerPos.symbol); 
    // I DONT THINK WE NEED THIS AFTER I IMPLEMENTED THE DRAWBOARD.
}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{    

    delete myPlayer;
    delete myGM;
    MacUILib_uninit();
}
