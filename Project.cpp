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

    if(myGM->getInput() == 27){
        myGM -> setExitTrue();
    }
}

void DrawScreen(void)
{
    MacUILib_clearScreen();  
    int printed = 0;
    objPos playerPos = myPlayer -> getPlayerPos();

    for (int j = 0; j < myGM->getBoardSizeY(); j++) {
        for(int i = 0; i < myGM->getBoardSizeX(); i++) {
            if(playerPos.pos -> x == i &&  playerPos.pos -> y == j){
                MacUILib_printf("%c", playerPos.symbol);
            }
            else if(i == 5 && j == 5){
                MacUILib_printf("+");
            }
            else if(i == 12 && j == 2){
                MacUILib_printf("+");
            }
            else if(i == 7 && j == 7){
                MacUILib_printf("+");
            }    
            else if (j == 0 || j == 14 || i == 0 || i == 29) {
                MacUILib_printf("#");  
            } 
            else {
                MacUILib_printf(" "); 
            }
             
        }
        MacUILib_printf("\n");  
     }
    if(myGM->getExitFlagStatus() == true){
        MacUILib_printf("YOU EXITED THE GAME");
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
    MacUILib_clearScreen();    

    delete myPlayer;
    delete myGM;
    delete myPlayer;

    MacUILib_uninit();
}
