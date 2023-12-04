#ifndef _SABOTAGE_H_
#define _SABOTAGE_H_
#include <iostream>
#include <string>

using namespace std;
class Ability;

class Sabotage : public Ability {
    // put private fields/methods here if needed
    
    public:
    Sabotage();
    ~Sabotage();
    void activate(Player& player, Player& opponent ) override; // reads input and activates ability
};

#endif

