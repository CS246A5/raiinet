#include <iostream>
#include <string>
#include "ability.h"

using namespace std;

class LinkBoost : public Ability
{

public:
    LinkBoost();
    ~LinkBoost();
    void activate(Player &player, Player &opponent) override; // reads input and activates ability
};
