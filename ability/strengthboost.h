#ifndef _STRENGTHBOOST_H_
#define _STRENGTHBOOST_H_
#include <iostream>
#include <string>

using namespace std;
class Ability;

class StrengthBoost : public Ability {
    // put private fields/methods here if needed
    
    public:
    StrengthBoost();
    ~StrengthBoost();
    void activate(Player& player, Player& opponent ) override; // reads input and activates ability
};
#endif
