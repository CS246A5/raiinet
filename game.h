#include <iostream>
#include <string>
#include "board.h"
#include "textdisplay.h"
#include "player.h"

class Player;

class Game {
    Player p1; // for more than two players, can do an arr/vec of players
    Player p2;
    Board b;
    bool whoseTurn = true;     // true for playerOne, false for playerTwo 
                        // for more than two players, can make integer
    TextDisplay *td;
    // TODO: add graphic display
    Player *theirTurn(bool who);

    public:
    Game();
    ~Game();
    Player *getCurrentPlayer();
    void initPlayerOne(Player player1);
    void initPlayerTwo(Player player2);
    bool checkFinished();   // check if the game has finished- check if any player
                            // has 4 viruses or 4 data
    void toggleTurn(); // switch to other player's turn
    void init(); // attaches td as an observer to every Cell on theBoard
    void useAbility(int i); // uses the current player's ability at index i (0-4)
    void moveLink(char id, char dir);   // moves the current player's link by id in the dir direction
                                        // dir can be 'n', 'e', 's', 'w'
                                        // edits the board
    void updateBoard(); // updates board
    void printAbilities();
    friend std::ostream &operator<<(std::ostream &out, const Game &g);
};
