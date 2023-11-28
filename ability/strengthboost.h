#include <iostream>
#include <string>
#include "ability.h"

using namespace std;

class StrengthBoost : public Ability {
    // put private fields/methods here if needed
    
    public:
    StrengthBoost();
    ~StrengthBoost();
    void activate() override; // reads input and activates ability
};
