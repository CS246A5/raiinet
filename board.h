#include <iostream>
#include <string>
#include <vector>
#include "player.h"
#include "cell.h"

using namespace std;

class Board {
    Cell theBoard[8][8]; // an 8-by-8 array of Cells
    
    public:
    Board(); // default ctor
    ~Board();
    void init(Player p1, Player p2);
    friend std::ostream &operator<<(std::ostream &out, const Board &b);
};
