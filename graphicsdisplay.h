#ifndef _GRAPHICDISPLAY_H_
#define _GRAPHICDISPLAY_H_
#include <iostream>
#include <string>

using namespace std;

class Xwindow;
class Game;
class Player;

class Cell;

class GraphicsDisplay : public Observer {
    Xwindow& w;
    Game& g;
    int size; 
    bool whoseTurn; // true for playerOne, false for playerTwo

    public:
    GraphicsDisplay(Xwindow &w, Game& g);
    void setSize(int size);

    void notify(Cell &c) override; // my reaction to getting notified

    ~GraphicsDisplay();
};

#endif
