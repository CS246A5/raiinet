#include "download.h"
 // Constructor for download
Download::Download() : Ability("Download") {
   
}

//create destructor
Download::~Download() {

}

//create activate

void Download::activate(Player& player ) { 
    // Read input to determine which link to download 
    cout << "Enter the name or ID of the link you want to polarize: ";
    char linkName;

    while (true) {
        cin >> linkName;

        try {
            // Assuming Ability has a virtual getLink function
            Link& link = player.getLink(linkName);

            // Check if it has already been downloaded
            if (link.checkIfDownloaded()) {
                cout << "Link " << linkName << " has already been downloaded. Please reenter the link name: ";
            } else {
                // Change link to be downloaded
                link.setIsDownloaded(true);
                if (link.checkIfData()){
                    player.downloadData();
                } else {
                    player.downloadVirus();
                }
                cout << "Link " << linkName << " has been downloaded.\n";
                break; // Exit the loop since we found the link
            }
        } catch (const std::runtime_error& e) { //not sure if it is the right exception to catch
            // Specified link is not found
            cout << "Link not found. Please reenter the link name: ";
        }
    }
}




