#include "board.h"
#include "textdisplay.h"

Board::Board() {
    // Initialize the board cells, you can add your logic here
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            theBoard[i][j].setCoords(i, j);
        }
    }
}

Board::~Board() {
    // Destructor logic if needed
}

Cell* Board::getCell(int r, int c) {
    // Return a pointer to the desired cell
    if (r >= 0 && r < 8 && c >= 0 && c < 8) {
        return &theBoard[r][c];
    } else {
        // Handle invalid coordinates
        return nullptr;
    }
}

void Board::init(TextDisplay* td) {
    // Attach the TextDisplay observer to every Cell on theBoard
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            theBoard[i][j].attach(td); // Attach the observer to the cell
        }
    }
}

std::ostream& operator<<(std::ostream& out, const Board& b) {
    // Implement the operator<< to display the board as needed
    // You can access the cells using b.theBoard[r][c]
    return out;
}