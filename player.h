#ifndef __PLAYER_H__
#define __PLAYER_H__
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include "ability/ability.h"
#include "board.h"
#include "link.h"
//import each ability
#include "ability/ability.h"
#include "ability/linkboost.h"
#include "ability/firewall.h"
#include "ability/download.h"
#include "ability/polarize.h"
#include "ability/scan.h"
#include "ability/movelink.h"
#include "ability/sabotage.h"
#include "ability/strengthboost.h"


using namespace std;

class Player {
    protected: 
        map<char,Link> links;

    int numData; // # of downloaded data
    int numVirus; // # of downloaded viruses
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
        
        void downloadData(); //increment the number of data 
        void downloadVirus(); //increment the number of virus downloadedf

        Link& getLink(char id); // get link at id (a-h) or (A-H)

        void addAbility(char ability); // adds ability 'L', 'S', etc.
        void addLink(char id, string link); // adds link during setup. id is 'a','D', etc.
                                            // link is "V4", "D2", etc.
        void moveLink(char id, char direction); // moves link by id in specified
                                                                // direction. Updates link coords
        void useAbility(int i); // uses ability at index i
        void printAbilities(); //print the abilities avaliable
};

#endif
