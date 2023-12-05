#include "ability.h"
#include "sabotage.h"

#include "../board.h"
#include "../player.h"
#include "../game.h"

//create constructor
Sabotage::Sabotage(): Ability("Sabotage", move(theGame)) {}

//create destructor
Sabotage::~Sabotage() {}

//create activate
void Sabotage::activate(Player& player, Player& opponent ) { 
    // Read input to determine which link to sabotage 
    //cout << "Enter the ID of the link you want to move: ";
    char id;
    while (true) {
        cin >> id;

        Link& link = opponent.getLink(id);
        // Check if it has already been sabotaged
        if (link.checkIfSabotaged()) {
            cout << "Link " << id << " has already been sabotaged. Please re-enter the link id: ";
        } else {
            // set the link to sabotaged
            link.setIsSabotaged(true);
            setUsed(true);
            cout << "Link " << id << " has been sabotaged." << endl;
            break; // Exit the loop since we found the link
        }
    }
}






