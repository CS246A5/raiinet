#ifndef __FIREWALL_H__
#define __FIREWALL_H__
#include <iostream>
#include <string>

using namespace std;
class Ability;

class Firewall : public Ability
{
    // put private fields/methods here if needed
<<<<<<< HEAD

public:
=======
   // private:
    //Game& game;
    
    public:
>>>>>>> 88259d5d2be3f6c00c83cd58a9778abdf18b1d04
    Firewall();
    ~Firewall();
    void activate(Player &player, Player &opponent) override; // reads input and activates ability
};

#endif
