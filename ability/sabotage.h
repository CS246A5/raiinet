#include <iostream>
#include <string>
#include "ability.h"

using namespace std;

class Sabotage : public Ability {
    // put private fields/methods here if needed
    
    public:
    Sabotage();
    ~Sabotage();
    void activate() override; // reads input and activates ability
};
