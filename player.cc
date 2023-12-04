#include "player.h"

// constructor
Player::Player(Game *theGame): theGame{theGame}, numData{0}, numVirus{0} {
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
int Player::getNumData() const {
    return numData;
}

// getter for the number of downloaded viruses
int Player::getNumVirus() const {
    return numVirus;
}

//getter for number of abilities remaining unused
int Player::getNumAbilities() const {
    int count = 0;
    for (int i = 0; i < 5; ++i) {
        Ability* curr = abilities[i];
        if(!curr->checkUsed()) count++;
    }
    return count;
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

// add to numData or numVirus after download
void Player::downloadLink(Link& currLink) {
    if (currLink.checkIfData()){
        numVirus ++;
    } else {
        numData ++;
    }
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
    if (cIsData == 'V') isData = false;
 
    if(std::isupper(id)){
        int posX = 7;
        int posY = id - 'A' + 1;
        if (id == 'D' || id == 'E') posX -= 1;
        std::unique_ptr<Link> l  = std::make_unique<Link>(posX, posY, strength, isData);
        links[id] = *l;
        linkNames[id] = link;
    } else {
        int posX = 0;
        int posY = id - 'a' + 1;
        if (id == 'd' || id == 'e') posX += 1;
        std::unique_ptr<Link> l  = std::make_unique<Link>(posX, posY, strength, isData);
        links[id] = *l;
        linkNames[id] = link;
    }
}

// move a link in the specified direction
bool Player::moveLink(char id, char direction, bool isP1Turn) {
    bool isIllegal = false;

    Link& link = links[id];
    int posX = link.getPosX();
    int posY = link.getPosY();
    bool isBoosted = link.checkIfBoosted();
    
    int increment = 1;
    if (isBoosted) increment = 2;

    //check which direction the movement is and assume the positions are m oved
    switch (direction) {
        case 'N': posY -= increment;;
        case 'W': posX -= increment;
        case 'E': posX += increment;
        case 'S': posY += increment;
    }

    //check illegal moves
    //check if onto own links
    for (auto& p : links) {
        if (id == p.first) break; //if it is the link itself - should not check
        Link& otherLink = p.second;
        int otherX = otherLink.getPosX();
        int otherY = otherLink.getPosY();

        if(posX == otherX && posY == otherY) isIllegal = true;
    }

    //check if off map or server port
    if (isP1Turn){
        if ((posX == 3 || posX == 4) && posY == 0) { //own serverPort
            isIllegal = true;
        } else if ((posX > 7) || (posX < 0) || (posY< 0)){ //off the map
            isIllegal = true;
        }
    } else {
         if ((posX == 3 || posX == 4) && posY == 7) { //own serverPort
            isIllegal = true;
        } else if ((posX > 7) || (posX < 0) || (posY > 7)){ //off the map
            isIllegal = true;
        } 
    }

    //if illegal move return false
    if(isIllegal){
        cout << "Illegal move" << endl;
        return false;
    
    } else { //else make the necessary moves
        switch (direction) {
            case 'N': links[id].moveN();
            case 'W': links[id].moveW();
            case 'E': links[id].moveE();
            case 'S': links[id].moveS();
        }   
        return true;
    }
    
} //moveLink

// use an ability at the specified index
bool Player::useAbility(int i, Player &opponent ) {
    if (i >= 0 && i < 5 && abilities[i] != nullptr) {
        if(abilities[i]->checkUsed()) {
            abilities[i]->activate(*this, opponent);
        }
        else {
            //cout << "This ability has already been used"  << endl;
            return false;
        }
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


std::ostream &operator<<(std::ostream &out, const Player &p) {
    int count = 0;
    for (auto& p : p.linkNames){
        count++;
        out << p.first << ": " << p.second << " ";
        if (count == 4) out << endl;
    }
    return out;
}
