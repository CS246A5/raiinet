#include "game.h"

using namespace std;

// Player p1;
// Player p2;
// bool whoseTurn = true; // true for p1
// TextDisplay *td;
// Board theBoard;

Player *Game::theirTurn() {
    if (whoseTurn) return &p1;
    else return &p2;
}

Game::Game() : td{new TextDisplay} {}

Game::~Game() {}

void Game::initPlayerOne(Player player1) {p1 = player1;}

void Game::initPlayerTwo(Player player2) {p1 = player2;}

// check if the game has finished- check if any player
// has 4 viruses or 4 data
bool Game::checkFinished() {
    if (p1.getNumData() == 4 || p2.getNumVirus() == 4) {
        cout << "PLAYER 1 WINS!!" << endl;
        return true;
    }
    else if (p2.getNumData() == 4 || p1.getNumVirus() == 4) {
        cout << "PLAYER 2 WINS!!" << endl;
        return true;
    }
    return false;
}


void Game::toggleTurn() {
    whoseTurn = !whoseTurn;
}


void Game::init() {
    b.init(td);
}

// uses the current player's ability at index i (0-4)
void Game::useAbility(int i) {
    Player *curPlayer = theirTurn();
    curPlayer->useAbility(i);
}

// moves the current player's link by id in the dir direction
// dir can be 'n', 'e', 's', 'w'
// edits the board
void Game::moveLink(char id, char dir) {
    Player *curPlayer = theirTurn();

    // old position
    int posX = curPlayer->getLink(id).getPosX();
    int posY = curPlayer->getLink(id).getPosY();

    // change old cell
        // if was on firewall:
    if (b.theBoard[posX][posY].isPlayerOneFirewall()) b.theBoard[posX][posY].setState('m');
    else if (b.theBoard[posX][posY].isPlayerTwoFirewall()) b.theBoard[posX][posY].setState('w');
        // if normal cell
    else b.theBoard[posX][posY].setState('.');
    
    // moving
    curPlayer->moveLink(id, dir);
    // new position
    posX = curPlayer->getLink(id).getPosX();
    posY = curPlayer->getLink(id).getPosY();

    // if lands on Server port / download edge
    if (whoseTurn == true) { // p1's turn
        if ((posX == 3 || posX == 4) && (posY == 7)) { // server ports
            
        }

    }
    // updating the board
    int posX = curPlayer->getLink(id).getPosX();
    int posY = curPlayer->getLink(id).getPosY();
    
    

    // check if boosted
    bool isBoosted = curPlayer->getLink(id).checkIfBoosted();
} 

void Game::printAbilities();


std::ostream &operator<<(std::ostream &out, const Game &g);

