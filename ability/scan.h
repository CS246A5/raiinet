#include <iostream>
#include <string>
#include "ability.h"

using namespace std;

class Scan : public Ability {
    // put private fields/methods here if needed
    
    public:
    Scan();
    ~Scan();
    void activate() override; // reads input and activates ability
};
