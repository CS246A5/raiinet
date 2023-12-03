#include "../player.h"
#include "polarize.h"
#include <map>
#include <iostream>
#include <string>
#include <stdexcept>

class Player;

Polarize::Polarize(Player& playerRef) : Ability("Polarize"), player(playerRef) {
    // Constructor for Polarize
}

Polarize::~Polarize() { 
    // Destructor for Polarize
}

void Polarize::activate(Player& player, Player& opponent ) { 
    // Read input to determine which link to polarize 
    cout << "Enter the name or ID of the link you want to polarize: ";
    string linkName;

    while (true) {
        cin >> linkName;
    
        try{

        // Get the link from the map 
        Link& link = player.getLink[linkName[0]];
        
        // Assuming the map of links in the Player class is implemented 
        // Access the link by its ID 
        if (links.find(linkName[0]) == links.end()) {
            throw std::invalid_argument("Link not found.");
        }

        // Check if it's a data link or a virus link 
        if (link.checkIfData()) {
            // Change data link to a virus link with the same strength 
            link.setIsData(false);
            cout << "Link " << linkName << " has been polarized to a virus link.\n";
            } else {
                // Change virus link to a data link with the same strength
                link.setIsData(true);
                cout << "Link " << linkName << " has been polarized to a data link.\n";
            }
        }
        catch (const std::invalid_argument& e) {
            cout << e.what() << " Polarization failed.\n";
    }
}

}