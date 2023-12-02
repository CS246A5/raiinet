#include "linkboost.h"


 // Constructor for download
LinkBoost::LinkBoost() : Ability("LinkBoost") {
}

//create destructor
LinkBoost::~LinkBoost() {
}

//create activate

void LinkBoost::activate(Player& player, Player& opponent ) { 
    // Read input to determine which link to polarize 
    //cout << "Enter the ID of the link you want to boost: ";
    char id;

    while (true) {
        cin >> id;

        try {
            //get the link we want to work with
            Link& link = player.getLink(id);
            setUsed(true);
            // Check if the link is boosted
            if (link.checkIfBoosted()) {
                cout << "Link " << id << " has already been boosted. Please re-enter the link id: ";
            } else {
                link.setIsBoosted(true);
                cout << "Link " << id << " has been boosted.\n";
                break; 
            }
        } catch (const std::runtime_error& e) { //not sure if it is the right exception to catch
            // Specified link is not found
            cout << "Link not found. Please re-enter the link name: ";
        }
    }
}








