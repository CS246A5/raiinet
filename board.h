#ifndef _BOARD_H_
#define _BOARD_H_

#include <iostream>
#include <string>
#include <vector>
#include "player.h"
#include "cell.h"
#include "textdisplay.h"

using namespace std;

class Board {
    public:
    Cell theBoard[8][8]; // an 8-by-8 array of Cells
    static Board& getInstance();
    Board(); // default ctor
    ~Board();
    Cell *getCell(int r, int c); // gets cell at row r and column c
    void init(TextDisplay *td); // attaches td as an observer to every Cell on theBoard
    friend std::ostream &operator<<(std::ostream &out, const Board &b);
    void changeState(int r, int c, char newState);
};

#endif
