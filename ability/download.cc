
#include "ability.h"

#include "../board.h"
#include "../player.h"
#include "download.h"

using namespace std;

 // Constructor for download
Download::Download() : Ability("Download", move(theGame)) {}

//create destructor
Download::~Download() {}

//create activate

void Download::activate(Player& player, Player& opponent ) { 
    // Read input to determine which link to download 
    cout << "Enter the ID of the opponent link you want to download: ";
    char id;

    while (true) {
        cin >> id;

        try {
            // Assuming Ability has a virtual getLink function
            Link& link = opponent.getLink(id);

            // Check if it has already been downloaded
            if (link.checkIfDownloaded()) {
                cout << "Link " << id << " has already been downloaded. Please re-enter the link name: ";
            } else {
                // Change link to be downloaded
                link.setIsDownloaded(true);
                setUsed(true);
                opponent.downloadLink(link);
                cout << "Link " << id << " has been downloaded.\n";
                break; // Exit the loop since we found the link
            }
        } catch (const std::runtime_error& e) { //not sure if it is the right exception to catch
            // Specified link is not found
            cout << "Link not found. Please re-enter the link name: ";
        }
    }
}




