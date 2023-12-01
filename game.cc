#include "game.h"

using namespace std;

// Player p1;
// Player p2;
// bool whoseTurn = true; // true for p1
// TextDisplay *td;
// Board theBoard;

Player *Game::theirTurn(bool who) {
    if (who) return &p1;
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
    Player *curPlayer = theirTurn(whoseTurn);
    curPlayer->useAbility(i);
}

// moves the current player's link by id in the dir direction
// dir can be 'n', 'e', 's', 'w'
// edits the board
void Game::moveLink(char id, char dir) {
    Player *curPlayer = theirTurn(whoseTurn);
    Player *curOpponent = theirTurn(!whoseTurn);

    // old position
    int posX = curPlayer->getLink(id).getPosX();
    int posY = curPlayer->getLink(id).getPosY();

    // change old cell
        // if was on firewall:
    if (b.theBoard[posX][posY].isPlayerOneFirewall()) b.theBoard[posX][posY].setState('m');
    else if (b.theBoard[posX][posY].isPlayerTwoFirewall()) b.theBoard[posX][posY].setState('w');
        // if normal cell
    else b.theBoard[posX][posY].setState('.');

    // else TODO: deal with if it is undefined
    
    // moving
    curPlayer->moveLink(id, dir);
    // new position
    posX = curPlayer->getLink(id).getPosX();
    posY = curPlayer->getLink(id).getPosY();

    // if lands on Server port / download edge
    if (whoseTurn == true) { // p1's turn
        if ((posX == 3 || posX == 4) && posY == 7) { // p2's server ports
            curOpponent->downloadLink(curPlayer->getLink(id));
        }
        else if ((posY == 8 && posX != 3 && posX != 4)) { // p2's download edge
            curPlayer->downloadLink(curPlayer->getLink(id));
        }
    }
    else if (whoseTurn == false) { // p2's turn
        if ((posX == 3 || posX == 4) && posY == 0) { // p1's server ports
            curOpponent->downloadLink(curPlayer->getLink(id));
        }
        else if ((posY == -1) && posX != 3 && posX != 4) { //p1's download edge
            curPlayer->downloadLink(curPlayer->getLink(id));
        }
    }

    // if it lands on other player's firewall
    else if (whoseTurn == true && b.getCell(posY, posX)->isPlayerTwoFirewall() ||
        whoseTurn == false && b.getCell(posY, posX)->isPlayerOneFirewall()) {
        curPlayer->getLink(id).reveal();
        if (curPlayer->getLink(id).checkIfData() == false) {
            curPlayer->downloadLink(curPlayer->getLink(id));
        }
        b.changeState(posY, posX, id);
    }

    // if it lands on other player's link = BATTLE!!
        // the only cell states left should be '.' and '[link]'
    else if (b.getCell(posY, posX)->getState() != '.') {
        // at this point, it should be certain that the cell's state is the other player's link
        int curLinkLevel = curPlayer->getLink(id).getStrength();
        int oppLinkLevel = curOpponent->getLink(b.getCell(posY, posX)->getState()).getStrength();
        curPlayer->getLink(id).reveal();
        curOpponent->getLink(b.getCell(posY, posX)->getState()).reveal();
        
        if (curLinkLevel >= oppLinkLevel) { // if curPlayer wins
            curPlayer->downloadLink(curOpponent->getLink(b.getCell(posY, posX)->getState()));
            b.changeState(posY, posX, id);
        }
        else { // if curOpponent wins
            curOpponent->downloadLink(curPlayer->getLink(id));
        }
    }

    else { // lands on an empty cell: '.'
        b.changeState(posY, posX, id);
    }
} // moveLink

void Game::printAbilities() {
    Player *curPlayer = theirTurn(whoseTurn);
    curPlayer->printAbilities();
} // printAbilities


std::ostream &operator<<(std::ostream &out, const Game &g) {
    g.p1.
    out << "Player 1:" << endl;
    out << "Downloaded: " << 
}

