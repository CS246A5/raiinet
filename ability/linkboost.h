#ifndef _LINKBOOST_H_
#define _LINKBOOST_H_
#include "ability.h"
#include <iostream>
#include <string>

using namespace std;
class Ability;

class Player;
class Game;

class LinkBoost : public Ability
{

public:
    LinkBoost();
    ~LinkBoost();
<<<<<<< HEAD
    void activate(Player &player, Player &opponent) override; // reads input and activates ability
=======
    void activate(Player& player, Player& opponent) override; // reads input and activates ability
>>>>>>> 88259d5d2be3f6c00c83cd58a9778abdf18b1d04
};


#endif