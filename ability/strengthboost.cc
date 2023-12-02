#include "strengthboost.h"

//create constructor
StrengthBoost::StrengthBoost(): Ability("StrengthBoost") {}

//create destructor
StrengthBoost::~StrengthBoost() {}

//create activate
void StrengthBoost::activate(Player& player, Player& opponent ) { 
    // Read input to determine which link to boost strength 
    //cout << "Enter the ID of the link you want to move: ";
    char id;
     while (true) {
        cin >> id;
        try {
            Link& link = opponent.getLink(id);
            link.setStrength(link.getStrength() + 1);
            setUsed(true);
            cout << "Link " << id << " has been boosted in strength.\n";
            break; // Exit the loop since we found the link
        }catch (const std::runtime_error& e) { //not sure if it is the right exception to catch
            // Specified link is not found
            cout << "Link not found. Please re-enter the link name: ";
        }
    }
}






