#include <iostream>
#include <string>
#include <sstream>
#include "game.h"
// #include "player.h"

using namespace std;

enum class Direction { NORTH, EAST, SOUTH, WEST };

// converts from char to direction
Direction convert(const std::string &direction) {
    if ( direction == "e" ) return Direction::EAST;
    if ( direction == "w" ) return Direction::WEST;
    if ( direction == "n" ) return Direction::NORTH;
    else return Direction::SOUTH;
}

int main() {
    Game g;
    Player p1;
    Player p2;
    cout << "Welcome to RAIInet!" << endl;
    // setup
    string line;
    cout << "starting setup." << endl;

    // -ability1 <order>
    cout << "specify abilities for Player One using command: -ability1 <order>" << endl;
    cout << "Abilities:" << "\n" << "- L: Link Boost" << "\n" << "- F: Firewall"
    << "\n" << "- D: Download" << "\n" << "- P: Polarize" << "\n" << "- S: Scan"
    << "\n" << "- O: Move Link" << "\n" << "- A: Sabotage" << "\n" << "- T: Strength Boost" <<endl;
    cout << "example: -ability1 LFDSP" << "\n" << endl;
    
    string command;
    getline(cin, line);
    stringstream ss{line};
    while (ss >> command && command != "-ability1") {
        cout << "invalid command. Try again!" << "\n" << endl;
    }

    // adding the abilities
    char ability;
    bool needDefault = true; // check if the player did not specify abilities
    while (ss >> ability) {
        needDefault = false; // set to false
        p1.addAbility(ability);
    }
    // check if need default abilities
    if (needDefault == true) {
        p1.addAbility('L');
        p1.addAbility('F');
        p1.addAbility('D');
        p1.addAbility('S');
        p1.addAbility('P');
    }

    // TODO: just finished 

    

    

    while (cin >> command) {
        if (command == "-ability1") {
            /* 
            Abilities:
            - L: Link Boost
            - F: Firewall
            - D: Download
            - P: Polarize
            - S: Scan
            - O: Move Link
            - A: Sabotage
            - T: Strength Boost
            */
            
        }
    }

}




