#include "cell.h"
#include "observer.h"
#include "link.h"

// Default constructor
Cell::Cell() : sym('.'), r(-1), c(-1) {}

char Cell::getState() const {
    return sym;
}

void Cell::setState(char c) {
    sym = c;
    notifyObserver(); // Notify the observer when the state changes
}

void Cell::setPlayerOneFirewall() {
    playerOneFirewall = true;
}

void Cell::setPlayerTwoFirewall() {
    playerTwoFirewall = true;
}

bool Cell::isPlayerOneFirewall() const {
    return playerOneFirewall; 
}

bool Cell::isPlayerTwoFirewall() const {
    return playerTwoFirewall;
}

int Cell::getRow() const {
    return r;
}

int Cell::getColumn() const {
    return c;
}
 
void Cell::setCoords(int row, int col) {
    r = row;
    c = col;
}
void Cell::setLink(unique_ptr<Link> linkObj) {
    link = move(linkObj);
}

Link* Cell::getLink() const {  
    return link.get();
}


void Cell::attach(Observer* o) {
    observers.push_back(o);
}

// looping through the vector of observers and notifying each observer individually
void Cell::notifyObserver() {
    for (Observer* o : observers) {
        o->notify(*this);
    }
}

