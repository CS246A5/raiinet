// download.h
#ifndef __DOWNLOAD_H__
#define __DOWNLOAD_H__

#include <iostream>
#include <string>
#include "ability.h"

using namespace std;

class Download : public Ability {
    // put private fields/methods here if needed
    
    public:
    Download();
    ~Download();
    void activate(Player& player, Player& opponent ) override; // reads input and activates ability
};

#endif

