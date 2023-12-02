#include <iostream>
#include <string>
#include "ability.h"

using namespace std;

class MoveLink : public Ability {
    // put private fields/methods here if needed
    
    public:
    MoveLink();
    ~MoveLink();
    void activate(Player& player ) override;// reads input and activates ability
};
