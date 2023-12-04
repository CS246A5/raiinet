#ifndef _MOVELINK_H_
#define _MOVELINK_H_
#include <iostream>
#include <string>

using namespace std;
class Ability;

class MoveLink : public Ability {
    // put private fields/methods here if needed
    
    public:
    MoveLink();
    ~MoveLink();
    void activate(Player& player, Player& opponent )  override;// reads input and activates ability
};

#endif
