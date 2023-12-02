#include "sabotage.h"

//create constructor
Sabotage::Sabotage(): Ability("Sabotage") {}

//create destructor
Sabotage::~Sabotage() {}

//create activate
void Sabotage::activate(Player& player, Player& opponent ) { 
    // Read input to determine which link to sabotage 
    //cout << "Enter the ID of the link you want to move: ";
    char id;
    while (true) {
        cin >> id;

        try {
            Link& link = opponent.getLink(id);
            // Check if it has already been downloaded
            if (link.checkIfSabotaged()) {
                cout << "Link " << id << " has already been sabotaged. Please re-enter the link name: ";
            } else {
                // Change link to be downloaded
                link.setIsSabotaged(true);
                setUsed(true);
                cout << "Link " << id << " has been sabotaged.\n";
                break; // Exit the loop since we found the link
            }
        } catch (const std::runtime_error& e) { //not sure if it is the right exception to catch
            // Specified link is not found
            cout << "Link not found. Please re-enter the link name: ";
        }
    }
}






