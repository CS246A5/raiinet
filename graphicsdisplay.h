#ifndef _GRAPHICDISPLAY_H_
#define _GRAPHICDISPLAY_H_
#include <iostream>
#include <string>
#include "observer.h"
#include "cell.h"
#include "window.h"

using namespace std;

class GraphicsDisplay : public Observer {
    Xwindow w;
    int size; 
    bool whoseTurn; // true for playerOne, false for playerTwo

    public:
    GraphicsDisplay(Xwindow *w);
    void setSize(int size);

    void notify(Cell &c) override; // my reaction to getting notified

    ~GraphicsDisplay();
};

#endif
