#ifndef __CELL_H__
#define __CELL_H__
#include "observer.h"

using namespace std;

class Cell {
    char sym = '.'; // can be '.', 'w', 'm', 'a'-'g', 'A'-'G', etc.
    bool firewall = false;
    Observer *observer;
    int r, c; // row, column

    public:
    Cell(); // default constructor
    char getState() const; // returns the symbol at this cell
    bool checkIfFirewall() const; // returns true if this cell is a firewall
    int getRow() const; // returns r
    int getColumn() const; // returns c
    void setCoords(int r, int c); // set row and column numbers
    
    // void attach(Observer *o); // attaches observer
    void notifyObserver(); // alert my observer that my state has been changed
};

#endif
