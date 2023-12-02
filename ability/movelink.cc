#include "movelink.h"


//create constructor
MoveLink::MoveLink(): Ability("Move Link") {}

//create destructor
MoveLink::~MoveLink() {}

//create activate
void MoveLink::activate(Player& player, Player& opponent ) { 
    // Read input to determine which link to download 
    cout << "Enter the ID of the link you want to move: ";
    char id;
    int posX;
    int posY;
    while (true) {
        cin >> id >> posX >> posY;


    }
}





