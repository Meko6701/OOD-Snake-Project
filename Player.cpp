#include "Player.h"

Player::Player(GameMechs* thisGMRef) {
    mainGameMechsRef = thisGMRef;
    myDir = STOP;
    score = 0;
    hasEatenFood = false;

    // Set the initial position for the object in the center coordinaates of the board
    int centerX = mainGameMechsRef->getBoardSizeX() / 2;
    int centerY = mainGameMechsRef->getBoardSizeY() / 2;
    objPos initialPos(centerX, centerY, '$'); 
    playerPosList = new objPosArrayList();
    playerPosList->insertHead(initialPos); 
}


int Player::getScore() const {
    if (playerPosList != nullptr) {
        // Subtract 1 so you can exclude the head of the list from the score
        return playerPosList->getSize() - 1; 
    }
    return 0; 
}

// Destructor for the Player class

Player::~Player()
{
    delete playerPosList;
}


objPosArrayList* Player::getPlayerPosList() 
{
    return playerPosList;
}

void Player::updatePlayerDir()
{
    char input = mainGameMechsRef->getInput();
    switch (input) {
                case 9:  
                    mainGameMechsRef->setExitTrue(); 
                    break;
                 case ('W'):
                    if (myDir != DOWN){
                        myDir = UP;

                    }
                    break;
                case ('w'):
                    if (myDir != DOWN){
                        myDir = UP;

                    }
                    break;
                case ('A'):
                    if (myDir != RIGHT){
                        myDir = LEFT;
                    }

                    break;
                case ('a'):
                    if (myDir != RIGHT){
                        myDir = LEFT;
                    }
                    break;
                case ('S'):
                    if (myDir != UP){
                        myDir = DOWN;
                    }
                    break;
                case ('s'):
                    if (myDir != UP){
                        myDir = DOWN;
                    }                
                    break;
                case ('D'):
                    if (myDir != LEFT){
                        myDir = RIGHT;
                    }
                    break;
                case ('d'):
                    if (myDir != LEFT){
                        myDir = RIGHT;
                    }
                    break;
        

            default:
                break;
            }
        
        mainGameMechsRef->clearInput();
        
}

void Player::movePlayer() {
    objPos FirstElement;
    
    // Get the head position of the player/object
    playerPosList->getHeadElement(FirstElement);

    //Wrap around logic for player

    switch (myDir) {
        case UP:
            FirstElement.y = (FirstElement.y - 1 + mainGameMechsRef->getBoardSizeY() - 2) % (mainGameMechsRef->getBoardSizeY() - 2);
            break;
        case DOWN:
            FirstElement.y = (FirstElement.y + 1) % (mainGameMechsRef->getBoardSizeY() - 2);
            break;
        case LEFT:
            FirstElement.x = (FirstElement.x - 1 + mainGameMechsRef->getBoardSizeX() - 2) % (mainGameMechsRef->getBoardSizeX() - 2);
            break;
        case RIGHT:
            FirstElement.x = (FirstElement.x + 1) % (mainGameMechsRef->getBoardSizeX() - 2);
            break;
        default:
            break;
    }

    if (FirstElement.x <= 0) {
        FirstElement.x += (mainGameMechsRef->getBoardSizeX() - 2);
    }
    if (FirstElement.y <= 0) {
        FirstElement.y += (mainGameMechsRef->getBoardSizeY() - 2);
    }

    //checks for collision
    if (checkSelfCollision(FirstElement)) {
        mainGameMechsRef->setLoseFlag();
        return;
    }

    playerPosList->insertHead(FirstElement);

    if (!hasEatenFood) {
        playerPosList->removeTail();
    } else {
        hasEatenFood = false; 
    }

}


void Player::setHasEatenFood(bool hasEaten) {
    
    hasEatenFood = hasEaten;
}

bool Player::checkSelfCollision(const objPos& newHeadPos) const {
    
     bool collisionDetected = false;

    // Iterate's through the player/objects's body to check for any collision

    for (int i = 1; i < playerPosList->getSize(); ++i) {
        objPos part;
        playerPosList->getElement(part, i);

        if (part.x == newHeadPos.x && part.y == newHeadPos.y) {
            collisionDetected = true;
            break; 
        }
    }

    return collisionDetected;
}

void Player::increaseScore(int amount) {
    //incrementing score function
    score += amount;
}
