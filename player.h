#ifndef __PLAYER_H__
#define __PLAYER_H__
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include "ability/ability.h"
#include "link.h"

using namespace std;

class Player {
    int numData; // # of downloaded data
    int numVirus; // # of downloaded viruses
    map<char,Link> links;
    vector<Ability*> abilities;
    vector<int> firewalls;
    Ability convert(const char &direction) const; // converts from char to Ability

    public:
    enum class theAbilities { LINKBOOST, FIREWALL, DOWNLOAD, POLARIZE, 
                                SCAN, MOVELINK, SABOTAGE, STRENGTHBOOST };
    
    Player(); // ctor, might need fields for initialization
    ~Player();
    int getNumData(); // how many downloaded data
    int getNumVirus(); // how many downloaded virus
    void addAbility(char ability); // adds ability 'L', 'S', etc.
    void addLink(char id, string link); // adds link during setup. id is 'a','D', etc.
                                        // link is "V4", "D2", etc.
};

#endif
