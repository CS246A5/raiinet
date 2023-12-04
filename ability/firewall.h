#include <iostream>
#include <string>
#include "ability.h"

using namespace std;

class Firewall : public Ability {
    // put private fields/methods here if needed
    private:
    Game& game;
    Player player; 
    
    public:
    Firewall();
    ~Firewall();
    void activate(Player& player, Player& opponent ) override; // reads input and activates ability
};
