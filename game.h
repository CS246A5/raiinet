#include <iostream>
#include <string>
#include "board.h"
#include "textdisplay.h"
#include "player.h"

class Game {
    Board theBoard;
    Player playerOne; // for more than two players, can do an arr/vec of players
    Player playerTwo;
    bool whoseTurn;     // true for playerOne, false for playerTwo 
                        // for more than two players, can make integer
    TextDisplay *td;
    // TODO: add graphic display

    public:
    Game();
    ~Game();
    bool checkFinished();   // check if the game has finished- check if any player
                            // has 4 viruses or 4 data
    void toggleTurn(); // switch to other player's turn
    void attachObserver(); // attaches td as an observer to every Cell on theBoard
    void useAbility(int i); // uses the current player's ability at index i (0-4)
    void moveLink(char id, char dir);   // moves the current player's link by id in the dir direction
                                        // dir can be 'n', 'e', 's', 'w'
};
