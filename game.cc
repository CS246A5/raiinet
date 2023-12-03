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

Player *Game::getCurrentPlayer() {
    return theirTurn(whoseTurn);
}

Game::Game() : td{new TextDisplay}, p1{Player{this}}, p2{Player{this}} {
}

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
    td = new TextDisplay;
    b.init(td);
    // server ports
    b.getCell(0,3)->setState('S');
    b.getCell(0,4)->setState('S');
    b.getCell(7,3)->setState('S');
    b.getCell(7,4)->setState('S');

    // player 1
    b.getCell(0,0)->setState('a');
    b.getCell(0,1)->setState('b');
    b.getCell(0,2)->setState('c');
    b.getCell(1,3)->setState('d');
    b.getCell(1,4)->setState('e');
    b.getCell(0,5)->setState('f');
    b.getCell(0,6)->setState('g');
    b.getCell(0,7)->setState('h');

    // player 2
    b.getCell(7,0)->setState('A');
    b.getCell(7,1)->setState('B');
    b.getCell(7,2)->setState('C');
    b.getCell(6,3)->setState('D');
    b.getCell(6,4)->setState('E');
    b.getCell(7,5)->setState('F');
    b.getCell(7,6)->setState('G');
    b.getCell(7,7)->setState('H');

    // notify td
    td->notify(*b.getCell(0,3));
    td->notify(*b.getCell(0,4));
    td->notify(*b.getCell(7,3));
    td->notify(*b.getCell(7,4));

    td->notify(*b.getCell(0,0));
    td->notify(*b.getCell(0,1));
    td->notify(*b.getCell(0,2));
    td->notify(*b.getCell(1,3));
    td->notify(*b.getCell(1,4));
    td->notify(*b.getCell(0,5));
    td->notify(*b.getCell(0,6));
    td->notify(*b.getCell(0,7));

    td->notify(*b.getCell(7,0));
    td->notify(*b.getCell(7,1));
    td->notify(*b.getCell(7,2));
    td->notify(*b.getCell(6,3));
    td->notify(*b.getCell(6,4));
    td->notify(*b.getCell(7,5));
    td->notify(*b.getCell(7,6));
    td->notify(*b.getCell(7,7));
}

// uses the current player's ability at index i (0-4)
void Game::useAbility(int i) {
    Player *curPlayer = theirTurn(whoseTurn);
    Player *opponent = theirTurn(!whoseTurn);
    curPlayer->useAbility(i, *opponent);
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
    if (b.theBoard[posX][posY].isPlayerOneFirewall()) {
        b.theBoard[posX][posY].setState('m');
        b.getCell(posY, posX)->notifyObserver();
    }
    else if (b.theBoard[posX][posY].isPlayerTwoFirewall()) {
        b.theBoard[posX][posY].setState('w');
        b.getCell(posY, posX)->notifyObserver();
    }
        // if normal cell
    else {
        b.theBoard[posX][posY].setState('.');
        b.getCell(posY, posX)->notifyObserver();
    }

    // else TODO: deal with if it is undefined
    
    // moving
    curPlayer->moveLink(id, dir, whoseTurn);
    //if 
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
        b.getCell(posY, posX)->notifyObserver();
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
            b.getCell(posY, posX)->notifyObserver();
        }
        else { // if curOpponent wins
            curOpponent->downloadLink(curPlayer->getLink(id));
        }
    }

    else { // lands on an empty cell: '.'
        b.changeState(posY, posX, id);
        b.getCell(posY, posX)->notifyObserver();
    }
} // moveLink

void Game::printAbilities() {
    Player *curPlayer = theirTurn(whoseTurn);
    curPlayer->printAbilities();
} // printAbilities


std::ostream &operator<<(std::ostream &out, const Game &g) {
    out << "Player 1:" << endl;
    out << "Downloaded: " << g.p1.getNumData() << "D, " << g.p1.getNumVirus() << "V" << endl;
    out << "Abilities: " << g.p1.getNumAbilities() << endl;
    // printLinks
    out << "========" << endl;
    out << g.b;
    out << "========" << endl;
    out << "Player 1:" << endl;
    out << "Downloaded: " << g.p1.getNumData() << "D, " << g.p1.getNumVirus() << "V" << endl;
    out << "Abilities: " << g.p1.getNumAbilities() << endl;
    // printLinks
}
