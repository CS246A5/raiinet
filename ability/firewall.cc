#include "firewall.h"
#include "board.h" 
#include "game.h"
#include "player.h"
#include "textdisplay.h"
#include <iostream>
#include <string>

Firewall::Firewall() : Ability("Firewall", move(theGame)) {
}

Firewall::~Firewall() {
}

void Firewall::activate(Player& player, Player& opponent) {
    try {
        std::cout << "Enter the coordinates (row and column) to place the firewall: ";
        int row, col;
        std::cin >> row >> col;

        if (row < 0 || row >= 8 || col < 0 || col >= 8) {
            throw std::out_of_range("Coordinates are outside the board's dimensions.");
        }

        Board& gameBoard = Board::getInstance();
        Cell* selectedCell = gameBoard.getCell(row, col);

        if (selectedCell && selectedCell->getState() == '.') {
            char firewallSymbol = game.getCurrentPlayer() == &player ? 'm' : 'w';
            selectedCell->setState(firewallSymbol); // This will notify TextDisplay to update

        } else {
            std::cout << "Cannot place a firewall on an occupied square.\n";
        }
    } 
    catch (const std::out_of_range& e) {
        std::cout << "Error: " << e.what() << std::endl;
    }
    catch (const std::exception& e) {
        std::cout << "An unexpected error occurred: " << e.what() << std::endl;
    }
}

Board& Scan::getGameBoard() {
    return Board::getInstance();
}


