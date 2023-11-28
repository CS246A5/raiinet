#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
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
    cout << "starting setup." << endl;
    
    string line;
    while (getline(cin, line)) {
        stringstream ss{line};
        string command;
        ss >> command;
        
        if (command == "-ability1") {
            char ability;
            bool needDefault = true; // remains true if the player did not specify abilities
            while (ss >> ability) {
                needDefault = false; // set to false
                p1.addAbility(ability);
            }
            // if need default abilities
            if (needDefault == true) {
                p1.addAbility('L');
                p1.addAbility('F');
                p1.addAbility('D');
                p1.addAbility('S');
                p1.addAbility('P');
            }
        }

        if (command == "-ability2") {
            char ability;
            bool needDefault = true; // remains true if the player did not specify abilities
            while (ss >> ability) {
                needDefault = false; // set to false
                p2.addAbility(ability); // ability type is string
            }
            // if need default abilities
            if (needDefault == true) {
                p2.addAbility('L');
                p2.addAbility('F');
                p2.addAbility('D');
                p2.addAbility('S');
                p2.addAbility('P');
            }
        }

        if (command == "-link1") {
            string fileName;
            char ids ['a','b','c','d','e','f','g'];
            if (ss >> fileName) {
                fstream f {fileName};
                for (int i = 0; i < 8; ++i) {
                    string link;
                    f >> link;
                    p1.addLink(ids[i], link);
                }
            }
            else {
                // TODO: randomize module
            }     
        }

        // TODO: -link2

        if (command == "graphics") {
            cout << g << endl; // TODO: unsure
        }

    }
}




