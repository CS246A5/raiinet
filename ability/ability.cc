#include "ability.h"

//create constructor
Ability::Ability (const string& name, unique_ptr<Game> theGame) : id{-1}, isUsed{false}, theGame{theGame.get()} {
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


void Ability::setUsed(bool value) {
    isUsed = value;
}
