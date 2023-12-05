#ifndef __CELL_H__
#define __CELL_H__

#include <vector>
#include <string> // Include string explicitly
#include <memory>
#include "observer.h"
#include "link.h"

using namespace std;

class Link;

class Cell {
    char sym = '.'; // can be '.', 'w', 'm', 'a'-'g', 'A'-'G', etc.
    bool playerOneFirewall = false;
    bool playerTwoFirewall = false;
    std::vector<Observer*> observers; // Collection of observers
    int r, c; // row, column
    unique_ptr<Link> link = make_unique<Link>(0, 0, 0, true); // Pointer to a Link, null if the cell is empty

public:
    Cell(); // default constructor
    char getState() const; // returns the symbol at this cell
    void setState(char c); // sets sym to char c
    void setPlayerOneFirewall();
    void setPlayerTwoFirewall();
    bool isPlayerOneFirewall() const; // returns true if this cell is a firewall owned by p1
    bool isPlayerTwoFirewall() const; // returns true if this cell is a firewall owned by p2
    int getRow() const; // returns r
    int getColumn() const; // returns c
    void setCoords(int r, int c); // set row and column numbers
    void setLink(unique_ptr<Link> linkObj);
    Link* getLink() const;


    // Methods for attaching and detaching observers
    void attach(Observer* o);

    void notifyObserver(); // alert my observer that my state has been changed
};

#endif
