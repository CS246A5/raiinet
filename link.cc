#include "link.h"

// Default ctor
Link::Link() : posX{-1}, posY{-1}, strength{0}, isData{true} {}

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

//Setter for strength {
void Link::setStrength(int s){
    strength = s;
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

// Set isData
void Link::setIsData(bool value) {
    isData = value;
}

// Set IsDownloaded
void Link::setIsDownloaded(bool value) {
    isDownloaded = value;
}

// Set IsBoosted
void Link::setIsBoosted(bool value){
    isBoosted = value;
}


// Set isSabotaged
void Link::setIsSabotaged(bool value){
    isSabotaged = value;
}

//Set isRevealed to true
void Link::reveal(){
    isRevealed = true;
}

// Move the link north
void Link::moveN(int moveAmount) {
    posY -= moveAmount;
}

// Move the link east
void Link::moveE(int moveAmount) {
    posX += moveAmount;
}

// Move the link south
void Link::moveS(int moveAmount) {
    posY += moveAmount;
}

// Move the link west
void Link::moveW(int moveAmount) {
    posX -= moveAmount;
}