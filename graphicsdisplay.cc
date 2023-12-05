
#include <iostream>
#include <vector>
#include "game.h"
#include "player.h"
#include "board.h"
#include "observer.h"
#include "cell.h"
#include "window.h"
#include "graphicsdisplay.h"

using namespace std;

// creates an nxn display
GraphicsDisplay::GraphicsDisplay(Xwindow &w, Game& g) : w{w}, g{g} {
    w.fillRectangle(0, 0, 500, 500, 1);
    // Display Player 1
    Player* currentPlayer1 = g.theirTurn(true);
    w.drawString(10, 20, "Player 1:");
    // display Player 1 Downloaded and Abilities 
    w.drawString(10, 40, "Downloaded: " + std::to_string(currentPlayer1->getNumData()) + "D, " +
                         std::to_string(currentPlayer1->getNumVirus()) + "V");
    w.drawString(10, 60, "Abilities: " + std::to_string(currentPlayer1->getNumAbilities()));

    // Display Player 1 Links
    int linkX = 10, linkY = 80;
    int count = 0;
    for (char ch : {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'}) {
        count++;
        int strength = currentPlayer1->getPureLink(ch).getStrength();
        std::string linkType = (currentPlayer1->getPureLink(ch).checkIfData()) ? "D" : "V";
        std::string linkDisplay = (!g.checkWhoseTurn() && !currentPlayer1->getPureLink(ch).checkIfRevealed()) ? "?" : linkType + std::to_string(strength);
        
        w.drawString(linkX, linkY, ch + ": " + linkDisplay);
        linkX += 100;  // Adjust the spacing as needed
        if (count == 4) {
            linkY +=20;
            count = 0;
        } 
    }


    // Display the Board
    if (g.getBoard()) {
        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 8; ++j) {
                int cellSize = 50;  // Adjust the cell size as needed
                int x = 20 + j * cellSize;
                int y = 120 + i * cellSize;

                char sym = g.getBoard()->getCell(i, j)->getState();
                std::string msg = std::to_string(sym - '0');
                if(sym == '.') {
                    w.fillRectangle(x, y, cellSize, cellSize, Xwindow::Green);
                }  else {
                    w.fillRectangle(x, y, cellSize, cellSize, Xwindow::White);
                }
                w.drawString(x + cellSize / 2, y + cellSize / 2, msg);
            }
        }
    } else {
        w.drawString(200, 20, "Board not initialized.");
    }

    // Display Player 2
    Player* currentPlayer2 = g.theirTurn(false);
    linkX = 10, linkY = 550;  // Reset coordinates for Player 2
    w.drawString(10, 180, "Player 2:");
    // Display Player 2 Downloaded and Abilities (assuming you have appropriate getter functions)
    w.drawString(10, 200, "Downloaded: " + std::to_string(currentPlayer2->getNumData()) + "D, " +
                          std::to_string(currentPlayer2->getNumVirus()) + "V");
    w.drawString(10, 220, "Abilities: " + std::to_string(currentPlayer2->getNumAbilities()));

    // Display Player 2 Links
    count = 0;
    for (char ch : {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'}) {
        int strength = currentPlayer2->getPureLink(ch).getStrength();
        std::string linkType = (currentPlayer2->getPureLink(ch).checkIfData()) ? "D" : "V";
        std::string linkDisplay = (g.checkWhoseTurn() && !currentPlayer2->getPureLink(ch).checkIfRevealed()) ? "?" : linkType + std::to_string(strength);
        
        w.drawString(linkX, linkY, ch + ": " + linkDisplay);
        linkX += 100;  // adjust the spacing 
        if (count == 4) {
            linkY +=20;
            count = 0;
        } 
    }
}



void GraphicsDisplay::notify(Cell &c) {
    
    int cellSize = 50;
    int row = c.getRow();
    int col = c.getColumn();
    int x = 20 + col * cellSize;
    int y = 120 + row * cellSize;

    char sym = c.getState();
    std::string msg = std::to_string(sym - '0');
    if(sym == '.') {
        w.fillRectangle(x, y, cellSize, cellSize, Xwindow::Green);
    }  else {
        w.fillRectangle(x, y, cellSize, cellSize, Xwindow::White);
    }
    w.drawString(x + cellSize / 2, y + cellSize / 2, msg);
}

GraphicsDisplay::~GraphicsDisplay() {}

