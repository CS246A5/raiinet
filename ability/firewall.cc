#include "firewall.h"
#include "board.h" 
#include "game.h"
#include "player.h"
#include <iostream>
#include <string>

Firewall::Firewall(Game& gameRef) : game(gameRef), Ability("Firewall") {
}

Firewall::~Firewall() {
}

void Firewall::activate(Player& player, Player& opponent ) {
    
    cout << "Enter the coordinates (row and column) to place the firewall: ";
    int row, col;
    cin >> row >> col;

    Board& gameBoard = Board::getInstance(); 
    Player* currentPlayer = game.theirTurn(game.whoseTurn); 

    // Check if the selected square is empty
    Cell* selectedCell = gameBoard.getCell(row, col);
    if (selectedCell->getState() == '.') {
        // Place the firewall on the selected square
        if (selectedCell && selectedCell->getState() == '.'){
            char firewallSymbol = (currentPlayer.isPlayerOne()) ? 'm' : 'w':
            selectedCell->setState(firewallSymbol);

        // Check for opponent links on the same square
        // If opponent links are viruses, download them
        char opponentSymbol = (currentPlayer == Player::Player1) ? 'V' : 'D'; // Opponent's link symbols
        if (selectedCell->getState() == opponentSymbol) {
            currentPlayer.downloadLink(selectedCell);  // download the link
        }
        }
        // TODO:
        // Update the display and perform any other necessary actions
        // Implement functions to update the display and handle the game state
        // updateDisplay();
        // handleGameState();
    } else {
        // The selected square is not empty, firewall cannot be placed
        cout << "Cannot place a firewall on an occupied square.\n";
    }
}

Board& Scan::getGameBoard() {
    return Board::getInstance();
}


