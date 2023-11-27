#include <iostream>
#include <string>
#include "observer.h"

class TextDisplay : public Observer {
    char theDisplay[8][8];
    bool whoseTurn; // true for playerOne, false for playerTwo

    public:
    TextDisplay();
    ~TextDisplay();
    void notify(Cell &c) override; // my reaction to getting notified
    friend std::ostream &operator<<(std::ostream &out, const TextDisplay &td);
};
