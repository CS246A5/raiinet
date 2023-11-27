#include <iostream>
#include <string>
#include "board.h"

using namespace std;

class Ability {
    int id;              // the id of the ability
    bool isUsed = false; // has the ability been used yet?
    string abilityName;  // the name of the ability: Move Link, Sabotage, etc.

    public:
    Ability(); // ctor, might need fields for initialization
    virtual ~Ability() = 0;
    virtual void activate() = 0; // pure virtual function
    int getId();                 // returns the id of the ability
    bool checkUsed();            // returns whether the ability has been used
};
