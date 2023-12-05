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

    std::cout << "Welcome to RAIInet!" << endl;
    // setup
    bool linksSpecifiedOne = false;
    bool linksSpecifiedTwo = false;
    
    for (int i = 0; i < argc; ++i) {
        string command = argv[i];

        if (command == "-ability1") {
            if (i != argc-1 && argv[i+1][0] != '-') {
                for (int j = 0; j < 5; ++j) {
                    p1->addAbility(argv[i+1][j]);
                }
            }
            else {
                p1->addAbility('L');
                p1->addAbility('F');
                p1->addAbility('D');
                p1->addAbility('S');
                p1->addAbility('P');
            }
        }

        else if (command == "-ability2") {
            if (i != argc-1 && argv[i+1][0] != '-') {
                for (int j = 0; j < 5; ++j) {
                    p2->addAbility(argv[i+1][j]);
                }
            }
            else {
                p2->addAbility('L');
                p2->addAbility('F');
                p2->addAbility('D');
                p2->addAbility('S');
                p2->addAbility('P');
            }
        }

        else if (command == "-link1") {
            linksSpecifiedOne = true;
            string fileName;
            char ids[8] = {'a','b','c','d','e','f','g','h'};
            fileName = argv[i+1];
            fstream f {fileName};
            for (int i = 0; i < 8; ++i) {
                string link;
                f >> link;
                p1->addLink(ids[i], link);
            }
        }

        else if (command == "-link2") {
            linksSpecifiedOne = true;
            string fileName;
            char ids[8] = {'a','b','c','d','e','f','g','h'};
            fileName = argv[i+1];
            fstream f {fileName};
            for (int i = 0; i < 8; ++i) {
                string link;
                f >> link;
                p2->addLink(ids[i], link);
            }
        }

        else if (command == "graphics") {
            // TODO: make graphical thing
        }
    } // for loop

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

    if (g.checkWhoseTurn()) std::cout << "Player 1's turn." << endl;
    else std::cout << "Player 2's turn." << endl;

    // setup finished
    // interactions
    string line;
    istream& in = cin;
    while (getline(in, line)) {
        try {
            // print who's turn
            if (g.checkWhoseTurn()) std::cout << "Player 1's turn." << endl;
            else std::cout << "Player 2's turn." << endl;

            stringstream ss{line};
            string command;
            ss >> command;
            
            bool usedAbility = false;

            if (command == "move") {
                char linkId;
                char direction;
                ss >> linkId;
                ss >> direction;
                // directions can be 'north', 'east', 'south', 'west'
                g.moveLink(linkId, direction); // (*)
                std::cout << g;
                g.toggleTurn();
            }

            if (command == "abilities") {
                g.printAbilities();
            }

            if (command == "ability") {
                if (usedAbility) { // if ability has been used this turn
                    throw logic_error {"ability has already been used this turn."};
                }
                int index;
                ss >> index;
                g.useAbility(index-1); // (*)
                usedAbility = true; // ability has now been used this turn
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
        } // try
        catch (std::logic_error r) {
            std::cout << r.what() << endl;
            continue;
        } // catch
    } // while  
    
}




