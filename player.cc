#include "player.h"

// constructor
Player::Player(Game* theGame): theGame{theGame}, numData{0}, numVirus{0} {
    // initialize links and abilities and firewallls?
}

// destructor
Player::~Player() {
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


Game *Player::getGame() {
    return theGame;
}

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
        Ability* curr = abilities[i].get();
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
        cout << "Wrong id, please re-enter: " << endl;
        cin.ignore();
        cin >> newId;
        return getLink(newId);
    }
}

Link& Player::getPureLink(char id) {
    auto it = links.find(id);
    return it->second;  // Return the value associated with the key 'id'
}

bool Player::hasSabotagedLink() {
    for (auto i : links) {
        if (i.second.checkIfSabotaged()) {
            char choices[3] = {'a','b','c'};
            srand((int)time(0)); // seed for random based on time
            int correctIndex = (rand() % 3);
            cout << "You have a sabotaged link, " << i.first << "." << endl;
            cout << "You must guess either a, b, or c to try and fix it: ";
            char guess;
            cin >> guess;
            if (guess == choices[correctIndex]) {
                i.second.setIsSabotaged(false);
                cout << "Congrats, you have fixed your link!" << endl;
            }
            else cout << "Bummer, it's still sabotaged." << endl;
            break;
        }
    }
    return false;
}

// char ids[8] = {'a','b','c','d','e','f','g','h'};
//         vector<string> theLinks = {"D1", "D2", "D3", "D4", "V1", "V2", "V3", "V4"};
//         for (int i = 0; i < 8; ++i) {
//             srand((int)time(0)); // seed for random based on time
//             int index = (rand() % (8-i)); // get index of the link we take from theLinks randomly
//             p1->addLink(ids[i], theLinks[index]); // add this link to p1's links
//             theLinks.erase(theLinks.begin()+index); // remove this link from theLinks so no duplicate
//         } // for

// add to numData or numVirus after download
void Player::downloadLink(Link& currLink) {
    if (currLink.checkIfData()){
        numData ++;
    } else {
        numVirus ++;
    }
}

// add an ability based on the given character
void Player::addAbility(char ability) {
    int addCount = 0;
    for (int i = 0; i < 5; i++) {
        if (!abilities[i]) {
            addCount = 1;
            switch (ability) {
                case 'L': abilities[i] = make_unique<LinkBoost>(); break;
                case 'F': abilities[i] = make_unique<Firewall>(); break;
                case 'D': abilities[i] = make_unique<Download>(); break;
                case 'S': abilities[i] = make_unique<Scan>(); break;
                case 'P': abilities[i] = make_unique<Polarize>(); break;
                case 'M': abilities[i] = make_unique<MoveLink>(); break;
                case 'B': abilities[i] = make_unique<Sabotage>(); break;
                case 'T': abilities[i] = make_unique<StrengthBoost>(); break;
            }
            break;
        }
        if (addCount == 1) break;
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
        int posY = 7;
        int posX = id - 'A';
        if (id == 'D' || id == 'E') posY -= 1;
        std::unique_ptr<Link> l  = std::make_unique<Link>(posX, posY, strength, isData);
        links[id] = *l;
        linkNames[id] = link;
    } else {
        int posY = 0;
        int posX = id - 'a';
        if (id == 'd' || id == 'e') posY += 1;
        std::unique_ptr<Link> l  = std::make_unique<Link>(posX, posY, strength, isData);
        links[id] = *l;
        linkNames[id] = link;
    }
}

// move a link in the specified direction
void Player::moveLink(char id, char direction, bool isP1Turn) {
    // bool isIllegal = false;

    Link *link = &links[id];
    // int posX = links[id].getPosX();
    // int posY = links[id].getPosY();
    bool isBoosted = links[id].checkIfBoosted();
    
    int increment = 1;
    if (isBoosted) increment = 2;

    //check which direction the movement is and assume the positions are moved
    // switch (direction) {
    //     case 'n': posY -= increment;
    //     case 'w': posX -= increment;
    //     case 'e': posX += increment;
    //     case 's': posY += increment;
    // }
    if (direction == 'n') link->moveN(increment);
    else if (direction == 'w') link->moveW(increment);
    else if (direction == 'e') link->moveE(increment);
    else if (direction == 's') link->moveS(increment);


    //check illegal moves
    //check if onto own links
    // for (auto& p : links) {
    //     if (id == p.first) break; //if it is the link itself - should not check
    //     Link& otherLink = p.second;
    //     int otherX = otherLink.getPosX();
    //     int otherY = otherLink.getPosY();

    //     if(posX == otherX && posY == otherY) isIllegal = true;
    // }

    //check if off map or server port
    // if (isP1Turn){
    //     if ((posX == 3 || posX == 4) && posY == 0) { //own serverPort
    //         isIllegal = true;
    //     } else if ((posX > 7) || (posX < 0) || (posY< 0)){ //off the map
    //         isIllegal = true;
    //     }
    // } else {
    //      if ((posX == 3 || posX == 4) && posY == 7) { //own serverPort
    //         isIllegal = true;
    //     } else if ((posX > 7) || (posX < 0) || (posY > 7)){ //off the map
    //         isIllegal = true;
    //     } 
    // }

    //if illegal move return false
    // if(isIllegal){
    //     cout << "Illegal move" << endl;
    //     return false;
    
    // } else { //else make the necessary moves
        
        // return true;
    // }
    
} //moveLink

// use an ability at the specified index
void Player::useAbility(int i, Player &opponent ) {
    if (i >= 0 && i < 5 && abilities[i] != nullptr) {
        if(!abilities[i].get()->checkUsed()) {
            abilities[i].get()->activate(*this, opponent);
        }
        else {
            throw logic_error {"This ability has already been used"};
        }
    }
}

// print the available abilities
void Player::printAbilities() {
    cout << "Available Abilities: ";
    for (int i = 0; i < 5; ++i) {
        if (abilities[i] != nullptr) {
            string ifUsed = "✓";
            if (abilities[i]->checkUsed()){
                ifUsed = "x";
            }
            cout << abilities[i]->getAbility() << " " << ifUsed << "; ";
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
