#include "player.h"

// constructor
Player::Player(): numData{0}, numVirus{0} {
    // initialize links and abilities and firewallls?
}

// destructor
Player::~Player() {
    // delete dynamically allocated abilities
    for (int i = 0; i < 5; ++i) {
        delete abilities[i];
    }
}

// //  convert a character to an ability 
// Ability Player::convert(const char &ability) const { // need to implment all of ability subclasses for squiggly to go away
//     //use case?
//     switch (ability) {
//         case 'L': return LinkBoost();
//         case 'F': return Firewall();
//         case 'D': return Download();
//         case 'P': return Polarize();
//         case 'S': return Scan();
//         case 'M': return MoveLink() ;
//         case 'B': return Sabotage();
//         case 'T': return StrengthBoost();
//     }

    //if has to do with enum class
//     switch (ability) {
//         case 'L': return theAbilities::LINKBOOST;
//         case 'F': return theAbilities::FIREWALL;
//         case 'D': return theAbilities::DOWNLOAD;
//         case 'P': return theAbilities::POLARIZE;
//         case 'S': return theAbilities::SCAN;
//         case 'O': return theAbilities::MOVELINK;
//         case 'A': return theAbilities::SABOTAGE;
//         case 'T': return theAbilities::STRENGTHBOOST;
//         default:  return theAbilities::UNKNOWN;
//     }
// }



// getter for the number of downloaded data
int Player::getNumData() {
    return numData;
}

// getter for the number of downloaded viruses
int Player::getNumVirus() {
    return numVirus;
}

// getter for a specific link
Link& Player::getLink(char id) {
    auto it = links.find(id);
    if (it != links.end()) {
        return it->second;  // Return the value associated with the key 'id'
    } else {
        char newId;
        // Handle the case when 'id' is not found in the map
        cout << "Wrong id, please reenter: ";
        cin >> newId;
        getLink(newId);
    }
}

// add to numData after download
void Player::downloadData() {
    numData++;
}
// add to numVirus after download
void Player::downloadVirus() {
    numVirus++;
} 

// add an ability based on the given character
void Player::addAbility(char ability) {
    for (int i = 0; i < 5; i ++ ){
        switch (ability) {
            case 'L': abilities[i] = new LinkBoost();
            case 'F': abilities[i] = new Firewall();
            case 'D': abilities[i] = new Download();
            case 'P': abilities[i] = new Polarize();
            case 'S': abilities[i] = new Scan();
            case 'M': abilities[i] = new MoveLink() ;
            case 'B': abilities[i] = new Sabotage();
            case 'T': abilities[i] = new StrengthBoost();
        }
    }
}

//Link(int posX, int posY, int strength, bool isData); 

// add a link during setup
void Player::addLink(char id, string link) {
    //convert string link into strength and boolean for data or virus
    //convert strength to int
    char cStrength = link[1];
    int strength = cStrength - '0';

    char cIsData = link[0];
    bool isData = true;
    if (cIsData = 'V') false;
 
    if(std::isupper(id)){
        int posX = 7;
        int posY = id - 'A' + 1;
        if (id == 'D' || id == 'E') posX -= 1;
        links.emplace(id, new Link(posX, posY, strength, isData));
     
    } else {
        int posX = 0;
        int posY = id - 'a' + 1;
        if (id == 'd' || id == 'e') posX += 1;
        links.emplace(id, new Link(posX, posY, strength, isData));
     
    }
}

// move a link in the specified direction
void Player::moveLink(char id, char direction) {
    switch (direction) {
            case 'N': links[id].moveN();
            case 'W': links[id].moveW();
            case 'E': links[id].moveE();
            case 'S': links[id].moveS();
        }
}

// use an ability at the specified index
void Player::useAbility(int i) {
    if (i >= 0 && i < 5 && abilities[i] != nullptr) {
        abilities[i]->activate(*this);
    }
}

// print the available abilities
void Player::printAbilities() {
    cout << "Available Abilities: ";
    for (int i = 0; i < 5; ++i) {
        if (abilities[i] != nullptr) {
            string ifUsed = "has not been used";
            if (abilities[i]->checkUsed()){
                ifUsed = "has been used";
            }
            cout << abilities[i]->getAbility() << " " << abilities[i]->checkUsed() <<" ";
        }
    }
    cout << endl;
}

