#include "graphicsdisplay.h"
#include "window.h"
#include "cell.h"
#include <iostream>
#include <vector>

using namespace std;

// creates an nxn display
GraphicsDisplay::GraphicsDisplay(Xwindow *w) : w{*w}, size{0} {
    w->fillRectangle(0, 0, 500, 500, 1);
}

void GraphicsDisplay::setSize(int newSize) {size = newSize;}


void GraphicsDisplay::notify(Cell &c) {
    
    // int newDim = 500 / size;
    // if (c.getState()) {
    //     w.fillRectangle(c.getCol() * newDim, c.getRow() * newDim, newDim, newDim, 0);
    // }
    // else w.fillRectangle(c.getCol() * newDim, c.getRow() * newDim, newDim, newDim, 1);
}

GraphicsDisplay::~GraphicsDisplay() {}

