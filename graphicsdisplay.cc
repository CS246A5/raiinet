
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
    w.fillRectangle(0, 0, 700, 1500, 0);
    // display Player 1
    Player* currentPlayer1 = g.theirTurn(true);
    w.drawString(10, 20, "Player 1:");
    // display Player 1 Downloaded and Abilities 
    w.drawString(10, 40, "Downloaded: " + std::to_string(currentPlayer1->getNumData()) + "D, " +
                         std::to_string(currentPlayer1->getNumVirus()) + "V");
    w.drawString(10, 60, "Abilities: " + std::to_string(currentPlayer1->getNumAbilities()));

    // display Player 1 Links
    int linkX = 20, linkY = 80;
    int count = 0;
    for (char ch : {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'}) {
        count++;
        int strength = currentPlayer1->getPureLink(ch).getStrength();
        string sChar (1,ch);
        string linkType = (currentPlayer1->getPureLink(ch).checkIfData()) ? "D" : "V";
        string linkDisplay = (!g.checkWhoseTurn() && !currentPlayer1->getPureLink(ch).checkIfRevealed()) ? "?" : linkType + std::to_string(strength);
        
        w.drawString(linkX, linkY, sChar + ": " + linkDisplay);
        linkX += 50;  // Adjust the spacing as needed
       
    }


    // Display the Board at initialization
    if (g.getBoard()) {
        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 8; ++j) {
                int cellSize = 50;  
                int x = 20 + j * cellSize;
                int y = 120 + i * cellSize;

                char sym = g.getBoard()->getCell(i, j)->getState();
                std::string msg (1,sym);
                if(sym == '.') {
                    w.fillRectangle(x, y, cellSize, cellSize, Xwindow::White);
                    w.drawString(x + cellSize / 2, y + cellSize / 2, msg);
                }  else {
                    w.fillRectangle(x, y, cellSize, cellSize, Xwindow::Black);
                    w.drawString(x + cellSize / 2, y + cellSize / 2, msg, Xwindow::White);
                }
                
            }
        }
    } else {
        w.drawString(200, 20, "Board not initialized.");
    }

    // display Player 2
    Player* currentPlayer2 = g.theirTurn(false);
    linkX = 20, linkY = 600;  // reset coordinates for Player 2
    w.drawString(10, 540, "Player 2:");
    // display Player 2 Downloaded and Abilities 
    w.drawString(10, 560, "Downloaded: " + std::to_string(currentPlayer2->getNumData()) + "D, " +
                          std::to_string(currentPlayer2->getNumVirus()) + "V");
    w.drawString(10, 580, "Abilities: " + std::to_string(currentPlayer2->getNumAbilities()));

    // display Player 2 Links
    count = 0;
    for (char ch : {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'}) {
        string sChar (1,ch);
        int strength = currentPlayer2->getPureLink(ch).getStrength();
        string linkType = (currentPlayer2->getPureLink(ch).checkIfData()) ? "D" : "V";
        string linkDisplay = (g.checkWhoseTurn() && !currentPlayer2->getPureLink(ch).checkIfRevealed()) ? "?" : linkType + to_string(strength);
        
        w.drawString(linkX, linkY, sChar + ": " + linkDisplay);
        linkX += 50;  // adjust the spacing 
        
    }
}



void GraphicsDisplay::notify(Cell &c) {
    
    int cellSize = 50;
    int row = c.getRow();
    int col = c.getColumn();
    int x = 20 + col * cellSize;
    int y = 120 + row * cellSize;
        
    char sym = c.getState();
    
    Player* currentPlayer1 = g.getCurrentPlayer();
    int strength = currentPlayer1->getPureLink(sym).getStrength();
    string linkType = (currentPlayer1->getPureLink(sym).checkIfData()) ? "D" : "V";
    string linkDisplay = (currentPlayer1->getPureLink(sym).checkIfRevealed()) ? "?" : linkType + std::to_string(strength);

    std::string msg(1,sym);
    if(sym == '.') {
        w.fillRectangle(x, y, cellSize, cellSize, Xwindow::White);
        w.drawString(x + cellSize / 2, y + cellSize / 2, msg);
    } else if (linkDisplay == "?") {
        w.fillRectangle(x, y, cellSize, cellSize, Xwindow::Black);
        w.drawString(x + cellSize / 2, y + cellSize / 2, msg, Xwindow::White);
    } else if (linkType == "D") {
        w.fillRectangle(x, y, cellSize, cellSize, Xwindow::Green);
        w.drawString(x + cellSize / 2, y + cellSize / 2, msg, Xwindow::White);
    } else if (linkType == "V") {
        w.fillRectangle(x, y, cellSize, cellSize, Xwindow::Red);
        w.drawString(x + cellSize / 2, y + cellSize / 2, msg, Xwindow::White);
    }
    

}

GraphicsDisplay::~GraphicsDisplay() {}

