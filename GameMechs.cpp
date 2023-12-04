
#include "GameMechs.h"
#include "MacUILib.h"

GameMechs::GameMechs()
{

}

GameMechs::GameMechs(int boardX, int boardY) : boardSizeX(boardX), boardSizeY(boardY), input(0), exitFlag(false) {

}

// do you need a destructor?



bool GameMechs::getExitFlagStatus()
{
    return exitFlag;
}

bool GameMechs::getLoseFlagStatus()
{
    return loseFlag;
}

char GameMechs::getInput() {
    if (MacUILib_hasChar() != 0)
        input = MacUILib_getChar();
    return input;
}

int GameMechs::getBoardSizeX()
{
    return boardSizeX;
}

int GameMechs::getBoardSizeY()
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

void GameMechs::generateFood(objPos *playerPos, objPosArrayList *snakeBody) {
    int XPosition;
    int YPosition;
    bool Different;
    //do-while loop to generate the food at random positons
    do {
        // Generate random X and Y positions within the board boundaries

        XPosition = rand() % boardSizeX;
        YPosition = rand() % boardSizeY;
        Different = false;

        if (XPosition == playerPos->x && YPosition == playerPos->y) {
            Different = true;
        }

        int i = 0;
        while (i < snakeBody->getSize()) {
            objPos part;
            snakeBody->getElement(part, i);
            if (part.x == XPosition && part.y == YPosition) {
                Different = true;
                break;
            }
            ++i;
        }
        // Checks if the generated position is within the board boundaries

        if (XPosition == boardSizeX - 1 || YPosition == boardSizeY - 1 || XPosition == 0 || YPosition == 0) {
            Different = true;
        }

    } while (Different);

    foodPos.setObjPos(XPosition, YPosition, 'O');


}


void GameMechs::getFoodPos(objPos &returnPos) {
    returnPos = foodPos;
}
