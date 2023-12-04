#include "ability.h"
#include "../player.h"
#include "polarize.h"
#include <iostream>
#include <string>
#include <stdexcept>

class Player;

Polarize::Polarize() : Ability("Polarize", move(theGame)) {
      // Constructor for Polarize
}

void Polarize::activate(Player& player, Player& opponent) { 
    cout << "Enter the name or ID of the link you want to polarize: ";
    string linkName;

    while (true) {
        cin >> linkName;

        try {
            // Get the link from the player
            Link& link = player.getLink(linkName[0]);

            // Check if it's a data link or a virus link 
            if (link.checkIfData()) {
                link.setIsData(false);
                cout << "Link " << linkName << " has been polarized to a virus link.\n";
                break;  // Exit loop after successful polarization
            } else {
                link.setIsData(true);
                cout << "Link " << linkName << " has been polarized to a data link.\n";
                break;  // Exit loop after successful polarization
            }
        } catch (const std::invalid_argument& e) {
            cout << e.what() << " Please try again.\n";
        }
    }
}
