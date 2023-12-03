#include "scan.h"
#include "board.h" 
#include <iostream>
#include <string>

Scan::Scan() : Ability("Scan") {
    // Constructor for Scan
}

Scan::~Scan() {
    // Destructor for Scan
}

void Scan::activate(Player& player, Player& opponent ) {
    
    // Read input to determine where to perform the scan
    cout << "Enter the coordinates (row and column) to perform the scan: ";
    int row, col;
    cin >> row >> col;

    Board& gameBoard = Board::getInstance(); 

    // Check if the selected square is within the board's dimensions
    if (row >= 0 && row < 8 && col >= 0 && col < 8) {
        // Get the cell at the selected coordinates
        Cell* selectedCell = gameBoard.getCell(row, col);

        // Check if the cell is occupied by a link
        char cellState = selectedCell->getState();
        if (cellState == 'V' || cellState == 'D') {
            // The cell contains a link (either virus or data)
            // Determine the type and strength of the link
            char linkType = (cellState == 'V') ? 'V' : 'D';
            int linkStrength = selectedCell->getLinkStrength();

            // Display the information to the player
            cout << "Scanning reveals a " << linkType << " link with strength " << linkStrength << ".\n";
        } else {
            // The cell does not contain a link
            cout << "Scanning reveals an empty square.\n";
        }
    } else {
        // The selected coordinates are outside the board's dimensions
        cout << "Invalid coordinates. Please select a square within the board's dimensions.\n";
    }
}

Board& Scan::getGameBoard() {
    return Board::getInstance();
}
