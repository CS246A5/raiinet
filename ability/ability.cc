#include "ability.h"

//create constructor
Ability::Ability (const string& name) : id{-1}, isUsed{false} {
    abilityName = name;
}

//destructor is pure virtual

//getter for ID
int Ability::getId() const{
    return id;
}

//getter for used - checkUsed()
bool Ability::checkUsed() const {
    return isUsed;
}

//getter for ability string
string Ability::getAbility() const{
    return abilityName;
}