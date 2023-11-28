#include <iostream>
#include <string>
#include "ability.h"

using namespace std;

class Download : public Ability {
    // put private fields/methods here if needed
    
    public:
    Download();
    ~Download();
    void activate() override; // reads input and activates ability
};
