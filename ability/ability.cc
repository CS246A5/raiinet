#include "ability.h"

//create constructor
Ability::Ability () : id{-1}, isUsed{false} {
    //string?
    abilityName = "";
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