#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <memory>
#include <ctime>
#include "game.h"
#include "player.h"
#include "ability/ability.h"

using namespace std;

int main(int argc, char* argv[]) {
    Game g;
    unique_ptr<Game> gp {&g};
    unique_ptr<Player> p1 = make_unique<Player>(gp.get());
    unique_ptr<Player> p2 = make_unique<Player>(gp.get());

    bool linksSpecifiedOne = false;
    bool linksSpecifiedTwo = false;

    std::cout << "Welcome to RAIInet!" << endl;
    // setup
    std::cout << "starting setup." << endl;
    
    for (int i = 0; i < argc; ++i) {
        
    }




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
                p1->addAbility(ability);
            }
            // if need default abilities
            if (needDefault == true) {
                p1->addAbility('L');
                p1->addAbility('F');
                p1->addAbility('D');
                p1->addAbility('S');
                p1->addAbility('P');
            }
        }

        if (command == "-ability2") {
            char ability;
            bool needDefault = true; // remains true if the player did not specify abilities
            while (ss >> ability) {
                needDefault = false; // set to false
                p2->addAbility(ability); // ability type is string
            }
            // if need default abilities
            if (needDefault == true) {
                p2->addAbility('L');
                p2->addAbility('F');
                p2->addAbility('D');
                p2->addAbility('S');
                p2->addAbility('P');
            }
        }

        if (command == "-link1") {
            linksSpecifiedOne = true;
            string fileName;
            char ids[8] = {'a','b','c','d','e','f','g','h'};
            ss >> fileName;
            fstream f {fileName};
            for (int i = 0; i < 8; ++i) {
                string link;
                f >> link;
                p1->addLink(ids[i], link);
            }
        }

        if (command == "-link2") {
            linksSpecifiedTwo = true;
            string fileName;
            char ids[8] = {'A','B','C','D','E','F','G','H'};
            ss >> fileName;
            fstream f {fileName};
            for (int i = 0; i < 8; ++i) {
                string link;
                f >> link;
                p1->addLink(ids[i], link);
            }
        }

        if (command == "graphics") {
            // if the links are not specified for each player
            if (!linksSpecifiedOne) {
                char ids[8] = {'a','b','c','d','e','f','g','h'};
                vector<string> theLinks = {"D1", "D2", "D3", "D4", "V1", "V2", "V3", "V4"};
                for (int i = 0; i < 8; ++i) {
                    srand((int)time(0)); // seed for random based on time
                    int index = (rand() % (8-i)); // get index of the link we take from theLinks randomly
                    p1->addLink(ids[i], theLinks[index]); // add this link to p1's links
                    theLinks.erase(theLinks.begin()+index); // remove this link from theLinks so no duplicate
                } // for
            }

            else if (!linksSpecifiedTwo) {
                char ids[8] = {'A','B','C','D','E','F','G','H'};
                vector<string> theLinks = {"D1", "D2", "D3", "D4", "V1", "V2", "V3", "V4"};
                for (int i = 0; i < 8; ++i) {
                    srand((int)time(0)); // seed for random based on time
                    int index = (rand() % (8-i)); // get index of the link we take from theLinks randomly
                    p2->addLink(ids[i], theLinks[index]); // add this link to p1's links
                    theLinks.erase(theLinks.begin()+index); // remove this link from theLinks so no duplicate
                } // for
            }
            g.initPlayerOne(move(p1));
            g.initPlayerTwo(move(p2));
            g.init();
            std::cout << g << endl;
            break;
        }
    }

        // setup finished
        // interactions

    
    istream& in = cin;
    while (getline(in, line)) {
        stringstream ss{line};
        string command;
        ss >> command;
        
        bool usedAbility = false;

        if (command == "move") {
            char linkId;
            char direction;
            ss >> linkId;
            ss >> direction;
            // directions can be 'n', 'e', 's', 'w'
            g.moveLink(linkId, direction);
            std::cout << g;
            g.toggleTurn();
        }

        if (command == "abilities") {
            g.printAbilities();
        }

        if (command == "ability") {
            if (usedAbility) {
                cerr << "ability has already been used." << endl;
                continue;
            }
            int index;
            ss >> index;
            g.useAbility(index-1);
            usedAbility = true;
        }

        if (command == "board") {
            std::cout << g;
        }

        if (command == "sequence") {
            string fileName;
            ss >> fileName;
            fstream f {fileName};
            istream& in = f; // idk if this works
        }

        if (command == "quit" || cin.eof()) {
            break;
        }

        if (g.checkFinished()) { // Game::checkFinished might produce output
            break;
        }
    }   
    std::cout << "BYEEE";
}




