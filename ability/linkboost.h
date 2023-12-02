#include <iostream>
#include <string>
#include "ability.h"

using namespace std;

class LinkBoost : public Ability {
    // put private fields/methods here if needed
    
    public:
    LinkBoost();
    ~LinkBoost();
    void activate(Player& player, Player& opponent ) override; // reads input and activates ability
};
