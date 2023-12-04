#include <iostream>
#include <string>
#include "ability.h"

using namespace std;

class Polarize : public Ability
{

public:
    Polarize();
    ~Polarize();
    void activate(Player &player, Player &opponent) override; // reads input and activates ability
};
