#ifndef __PLAYER_H__
#define __PLAYER_H__
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include "ability/ability.h"
#include "board.h"
#include "link.h"

using namespace std;

class Player {
    int numData = 0; // # of downloaded data
    int numVirus = 0; // # of downloaded viruses
    map<char,Link> links;
    Ability* abilities[5];
    vector<int> firewalls;
    Ability convert(const char &ability) const; // converts from char to Ability

    public:
    enum class theAbilities { LINKBOOST, FIREWALL, DOWNLOAD, POLARIZE, 
                                SCAN, MOVELINK, SABOTAGE, STRENGTHBOOST };
    
    Player(); // must initialize all links
    ~Player();
    int getNumData(); // how many downloaded data
    int getNumVirus(); // how many downloaded virus
    void addAbility(char ability); // adds ability 'L', 'S', etc.
    void addLink(char id, string link); // adds link during setup. id is 'a','D', etc.
                                        // link is "V4", "D2", etc.
    void moveLink(char id, char direction); // moves link by id in specified
                                                            // direction. Updates link coords
    void printAbilities();
};

#endif
