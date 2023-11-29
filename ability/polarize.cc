#include "player.h"
#include "polarize.h"
#include <map>
#include <iostream>
#include <string>

Polarize::Polarize() : Ability("Polarize") {
    // Constructor for Polarize
}

Polarize::~Polarize() { 
    // Destructor for Polarize
}

void Polarize::activate() { 
    // Read input to determine which link to polarize 
    cout << "Enter the name or ID of the link you want to polarize: ";
    string linkName;
    cin >> linkName;

    // Assuming the map of links in the Player class is implemented 
    // Access the link by its ID 
    if (links.find(linkName[0]) != links.end()) {
        // Get the link from the map 
        Link& link = links[linkName[0]];

        // Check if it's a data link or a virus link 
        if (link.checkIfData()) {
            // Change data link to a virus link with the same strength 
            link.setIsData(false):
            cout << "Link " << linkName << " has been polarized to a virus link.\n";
        } else {
            // Change virus link to a data link with the same strength
            link.setIsData(true);
            cout << "Link " << linkName << " has been polarized to a data link.\n";
        }

        // Exit the loop since we found the link
        return;

    }

    // Specified link is not found
    cout << "Link not found. Polarization failed.\n";
}