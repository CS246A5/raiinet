#include "ability.h"
#include "firewall.h"
#include "../board.h"
#include "../player.h"
#include "../game.h"
<<<<<<< HEAD
#include "textdisplay.h"
#include <iostream>
#include <string>

Firewall::Firewall() : Ability("Firewall", move(theGame))
{
}
=======

Firewall::Firewall(): Ability("Firewall", move(theGame)) {}
>>>>>>> 88259d5d2be3f6c00c83cd58a9778abdf18b1d04

Firewall::~Firewall()
{
}

void Firewall::activate(Player &player, Player &opponent)
{
    try
    {
        std::cout << "Enter the coordinates (row and column) to place the firewall: ";
        int row, col;
        std::cin >> row >> col;

        if (row < 0 || row >= 8 || col < 0 || col >= 8)
        {
            throw std::out_of_range("Coordinates are outside the board's dimensions.");
        }

<<<<<<< HEAD
        Board &gameBoard = Board::getInstance();
        Cell *selectedCell = gameBoard.getCell(row, col);

        if (selectedCell && selectedCell->getState() == '.')
        {
            char firewallSymbol = game.getCurrentPlayer() == &player ? 'm' : 'w';
=======
        Board& gameBoard = Board::getInstance();
        Cell* selectedCell = gameBoard.getCell(row, col);
        if (selectedCell && selectedCell->getState() == '.') {
            char firewallSymbol = theGame.get()->getCurrentPlayer() == &player ? 'm' : 'w';
>>>>>>> 88259d5d2be3f6c00c83cd58a9778abdf18b1d04
            selectedCell->setState(firewallSymbol); // This will notify TextDisplay to update
        }
        else
        {
            std::cout << "Cannot place a firewall on an occupied square.\n";
        }
    }
    catch (const std::out_of_range &e)
    {
        std::cout << "Error: " << e.what() << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cout << "An unexpected error occurred: " << e.what() << std::endl;
    }
}
<<<<<<< HEAD
=======

// Board& Scan::getGameBoard() {
//     return Board::getInstance();
// }


>>>>>>> 88259d5d2be3f6c00c83cd58a9778abdf18b1d04
