#include "link.h"

// Constructor 
Link::Link(int x, int y, int str, bool data) : posX(x), posY(y), strength(str), isData(data) {}

// Destructor (if needed)
Link::~Link() {} 

// Getter for x-coordinate 
int Link::getPosX() { 
    return posX;
}

// Getter for y-coordinate 
int Link::getPosY() { 
    return posY;
}

// Setter for x-coordinate 
void Link::setPosX(int x) { 
    posX = x;
}

// Setter for y-coordinate 
void Link::setPosY(int y){
    posY = y;
}

// Getter for strength 
int Link::getStrength() {
    return strength;
}

// Check if the link is revealed to the opponent 
bool Link::checkIfRevealed() {
    return isRevealed;
}

// Check if the link is a data link
bool Link::checkIfData() {
    return isData;
}


// Check if the link is boosted
bool Link::checkIfBoosted() {
    return isBoosted;
}

// Check if the link is sabotaged for its owner's turn
bool Link::checkIfSabotaged() {
    return isSabotaged;
}


// Check if the link is a data link
bool Link::checkIfDownloaded() {
    return isDownloaded;
}


void Link::setIsData(bool value) {
    isData = value;
}

void Link::setIsDownloaded(bool value) {
    isDownloaded = value;
}

// Move the link north
void Link::moveN() {
    // Check if the link is boosted
    int moveAmount = isBoosted ? 2 : 1;
    posY -= moveAmount;
}

// Move the link east
void Link::moveE() {
    // Check if the link is boosted
    int moveAmount = isBoosted ? 2 : 1;
    posX += moveAmount;
}

// Move the link south
void Link::moveS() {
    // Check if the link is boosted
    int moveAmount = isBoosted ? 2 : 1;
    posY += moveAmount;
}

// Move the link west
void Link::moveW() {
    // Check if the link is boosted
    int moveAmount = isBoosted ? 2 : 1;
    posX -= moveAmount;
}