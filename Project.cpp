
#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "GameMechs.h"  // Include the GameMechs header
#include "Player.h" 
#include "objPosArrayList.h"
#include <time.h>

using namespace std;

#define DELAY_CONST 100000

class Player;

bool exitFlag;

GameMechs* myGM = nullptr;
Player* myPlayer = nullptr;

void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);



int main(void)
{

    Initialize();

    //While the game is not over, run all these functions
    while(myGM->getExitFlagStatus()!=true)  
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

    //random number generator with time
    srand((unsigned int)time(NULL));


    myGM = new GameMechs(26,13);
    myPlayer = new Player(myGM);

    // Initialize exit flag to false so the player keeps on playing

    exitFlag = false;


    objPos playerPosition;
    objPosArrayList* playerBody = myPlayer->getPlayerPosList();
    // Check's if the player's body exists and has elements in it

    if (playerBody && playerBody->getSize() > 0) {
        playerBody->getHeadElement(playerPosition);
    }

    // Generate's food for the player

    myGM->generateFood(&playerPosition, playerBody); 


}

void GetInput(void) {
    myGM->getInput();
}



void RunLogic(void) {
    myPlayer->updatePlayerDir();
    myPlayer->movePlayer();

    // Get the player's position

    
    objPosArrayList* playerBody = myPlayer->getPlayerPosList();
    objPos headPos;

        
    // To Check if the player's body exists and has elements

    if (playerBody && playerBody->getSize() > 0) {
        playerBody->getHeadElement(headPos);
    }
    // Get the position of the food 'O' in the game

    objPos foodPos;
    myGM->getFoodPos(foodPos);
    // Checks for collsion of the head of the player with the food spawned

    if (headPos.x == foodPos.x && headPos.y == foodPos.y) {
        myGM->generateFood(&headPos, playerBody); 
        myPlayer->setHasEatenFood(!false); 
    }
    myGM->clearInput();
}




void DrawScreen(void) {
    MacUILib_clearScreen();


    objPos Fposition;
    objPosArrayList* playerBody = myPlayer->getPlayerPosList();
    myGM->getFoodPos(Fposition);
   
    //for loop to draw the border and symbol inside of it
    for (int i = 0; i < myGM->getBoardSizeY(); i++) {
        for (int j = 0; j < myGM->getBoardSizeX(); j++) {
            bool Onscreen = false;

            for (int w = 0; w < playerBody->getSize(); w++) {
                objPos part;
                playerBody->getElement(part, w);

                if (j == part.x && i == part.y) {
                    MacUILib_printf("%c", part.symbol);
                    Onscreen = true;
                    break;
                }
            }

            // Checks if the position is not filled by the snake body

            if (!Onscreen) {
                if (i == 0 || i == myGM->getBoardSizeY() - 1 || j == 0 || j == myGM->getBoardSizeX() - 1) {
                    MacUILib_printf("%c", '#');
                } else if (j == Fposition.x && i == Fposition.y) {
                    MacUILib_printf("%c", Fposition.symbol);
                } else {
                    MacUILib_printf(" ");
                }
            }
        }
        MacUILib_printf("\n");
    }

    MacUILib_printf("\n");

    // if statment to check if the player has lost, then it sets exit flag to be true and exits game.
    if (myGM->getLoseFlagStatus() == false) {
        MacUILib_printf("\t\t\t\t+++++++++ Made by Malek Abouelkhair and Mohamed Alkouni +++++++++\n");

        MacUILib_printf("Food at: <%d, %d>\n", Fposition.x, Fposition.y);
        MacUILib_printf("\nScore: %d\n", myPlayer->getScore());
        MacUILib_printf("\nPress TAB to exit\n");


    } else {
        MacUILib_printf("\t\t\t\t+++++++++ Made by Malek Abouelkhair and Mohamed Alkouni +++++++++");
        //End screen comments
        MacUILib_printf("\n!!!!!GAME OVER!!!!!\n");
        MacUILib_printf("\nFinal Score: %d\n", myPlayer->getScore());

        MacUILib_printf("\nPress TAB to exit\n");
        myGM->setExitTrue();
    }





}


void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); 
}


void CleanUp(void)
{
    delete myPlayer;  //deallocating memory for myPlayer
    delete myGM;      //deallocating memory for myGM
   
  
    MacUILib_uninit();
}

