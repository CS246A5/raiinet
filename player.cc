#include "player.h"

// constructor
Player::Player(): numData{0}, numVirus{0} {
    // initialize links and abilities and firewallls
}

// destructor
Player::~Player() {
    // delete dynamically allocated abilities
    for (int i = 0; i < 5; ++i) {
        delete abilities[i];
    }
}

//  convert a character to an ability enum
Ability Player::convert(const char &ability) const { // need to implment all of ability subclasses for squiggly to go away
    switch (ability) {
        //case 'L': return Ability::LINKBOOST; etc
    }
}

// getter for the number of downloaded data
int Player::getNumData() {
    return numData;
}

// getter for the number of downloaded viruses
int Player::getNumVirus() {
    return numVirus;
}

// getter for a specific link
Link Player::getLink(char id) {
    return links[id];
}

// add an ability based on the given character
void Player::addAbility(char ability) {
   //
}

// add a link during setup
void Player::addLink(char id, string link) {
   //links[id].setLink(link); //maybe add setLink in link.h and .cc
}

// move a link in the specified direction
void Player::moveLink(char id, char direction) {
    //if statement for the moves NWES
}

// use an ability at the specified index
void Player::useAbility(int i) {
    if (i >= 0 && i < 5 && abilities[i] != nullptr) {
        abilities[i].activate();
    }
}

// print the available abilities
void Player::printAbilities() {
    cout << "Available Abilities: ";
    for (int i = 0; i < 5; ++i) {
        if (abilities[i] != nullptr) {
            cout << abilities[i].getAbility() << " ";
        }
    }
    cout << endl;
}

