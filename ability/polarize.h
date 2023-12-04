#include <iostream>
#include <string>
#include "ability.h"

using namespace std;

class Polarize : public Ability {
    Player& player;
    // put private fields/methods here if needed
    
    public:
    Polarize(Player& playerRef);
    ~Polarize();
     void activate(Player& player, Player& opponent )  override; // reads input and activates ability
};
