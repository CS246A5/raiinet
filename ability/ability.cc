#include "ability.h"

//create constructor
Ability::Ability () : id{-1}, isUsed{false} {
}

//destructor is pure virtual

//getter for ID
int Ability::getId() {
    return id;
}

//getter for used - checkUsed()
bool Ability::checkUsed() {
    return isUsed;
}

//getter for ability string
string Ability::getAbility() {
    return abilityName;
}