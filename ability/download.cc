#include "download.h"
#include "../player.h"

 // Constructor for download
Download::Download() : Ability("Download") {
   
}

//create destructor
Download::~Download() {

}

//create activate

void Download::activate(Player& player ) { 
    // Read input to determine which link to polarize 
    cout << "Enter the name or ID of the link you want to polarize: ";
    char linkName;

    while (true) {
        cin >> linkName;

        try {
            // Assuming Ability has a virtual getLink function
            Link& link = player.getLink(linkName);

            // Check if it's a data link or a virus link 
            if (link.checkIfDownloaded()) {
                cout << "Link " << linkName << " has already been downloaded. Please reenter the link name: ";
            } else {
                // Change virus link to a data link with the same strength
                link.setIsDownloaded(true);
                cout << "Link " << linkName << " has been downloaded.\n";
                break; // Exit the loop since we found the link
            }
        } catch (const std::runtime_error& e) {
            // Specified link is not found
            cout << "Link not found. Please reenter the link name: ";
        }
    }
}




