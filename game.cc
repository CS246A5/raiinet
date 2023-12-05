#include "game.h"

using namespace std;

// Player p1;
// Player p2;
// bool whoseTurn = true; // true for p1
// TextDisplay *td;
// Board theBoard;

Player *Game::theirTurn(bool who)
{
    if (who)
        return p1.get();
    else
        return p2.get();
}

Player *Game::getCurrentPlayer()
{
    return theirTurn(whoseTurn);
}

Game::Game() : p1{nullptr}, p2{nullptr}, td{new TextDisplay}, gd{nullptr} {}

Game::~Game() {}

void Game::initPlayerOne(unique_ptr<Player> player1) { p1 = move(player1); }

void Game::initPlayerTwo(unique_ptr<Player> player2) { p2 = move(player2); }

bool Game::checkWhoseTurn() {
    return whoseTurn;
}

Board *Game::getBoard()
{
    return b.get();
}

// check if the game has finished- check if any player
// has 4 viruses or 4 data
bool Game::checkFinished()
{
    if (p1->getNumData() == 4 || p2->getNumVirus() == 4)
    {
        cout << "PLAYER 1 WINS!!" << endl;
        return true;
    }
    else if (p2->getNumData() == 4 || p1->getNumVirus() == 4)
    {
        cout << "PLAYER 2 WINS!!" << endl;
        return true;
    }
    return false;
}

void Game::toggleTurn()
{
    whoseTurn = !whoseTurn;
}

void Game::init()
{
    b->init(td.get());
    // server ports
    b->getCell(0, 3)->setState('S');
    b->getCell(0, 4)->setState('S');
    b->getCell(7, 3)->setState('S');
    b->getCell(7, 4)->setState('S');

    // player 1
    b->getCell(0, 0)->setState('a');
    b->getCell(0, 1)->setState('b');
    b->getCell(0, 2)->setState('c');
    b->getCell(1, 3)->setState('d');
    b->getCell(1, 4)->setState('e');
    b->getCell(0, 5)->setState('f');
    b->getCell(0, 6)->setState('g');
    b->getCell(0, 7)->setState('h');

    // player 2
    b->getCell(7, 0)->setState('A');
    b->getCell(7, 1)->setState('B');
    b->getCell(7, 2)->setState('C');
    b->getCell(6, 3)->setState('D');
    b->getCell(6, 4)->setState('E');
    b->getCell(7, 5)->setState('F');
    b->getCell(7, 6)->setState('G');
    b->getCell(7, 7)->setState('H');
}

// uses the current player's ability at index i (0-4)
void Game::useAbility(int i)
{
    Player *curPlayer = theirTurn(whoseTurn);
    Player *opponent = theirTurn(!whoseTurn);
    curPlayer->useAbility(i, *opponent);
}

// moves the current player's link by id in the dir direction
// dir can be 'n', 'e', 's', 'w'
// edits the board
void Game::moveLink(char id, char dir)
{
    Player *curPlayer = theirTurn(whoseTurn);
    Player *curOpponent = theirTurn(!whoseTurn);

    // old position
    int posX = curPlayer->getLink(id).getPosX();
    int posY = curPlayer->getLink(id).getPosY();

    // prepare opposite direction in case of throw
    char oppDir;
    if (dir == 'n') oppDir = 's';
    if (dir == 'e') oppDir = 'w';
    if (dir == 's') oppDir = 'n';
    if (dir == 'w') oppDir = 'e';

    // change old cell
    // if was on firewall:
    if (b->theBoard[posY][posX].isPlayerOneFirewall())
    {
        b->theBoard[posY][posX].setState('m');
    }
    else if (b->theBoard[posY][posX].isPlayerTwoFirewall())
    {
        b->theBoard[posY][posX].setState('w');
    }
    // if normal cell
    else
    {
        b->theBoard[posY][posX].setState('.');
    }

    // moving
    curPlayer->moveLink(id, dir, whoseTurn);

    cout << posX << posY;

    //  new position
    posX = curPlayer->getLink(id).getPosX();
    posY = curPlayer->getLink(id).getPosY();

    cout << posX << posY;

    // if lands on Server port / download edge
    if (whoseTurn == true)
    { // p1's turn
        if ((posX == 3 || posX == 4) && posY == 7)
        { // p2's server ports
            curOpponent->downloadLink(curPlayer->getLink(id));
        }
        else if ((posY == 8 && posX != 3 && posX != 4))
        { // p2's download edge
            curPlayer->downloadLink(curPlayer->getLink(id));
        }
        else if ((posX == 3 || posX == 4) && posY == 0)
        { // own server port!?
            curPlayer->moveLink(id, oppDir, whoseTurn);
            throw logic_error {"You can't move your link onto your own Server Port"};
        }
        else if (posX > 7 || posY > 7 || posX < 0 || posY < 0)
        { // off the map!!?
            curPlayer->moveLink(id, oppDir, whoseTurn);
            throw logic_error {"You can't move your link off the board"};
        }
    }
    else if (whoseTurn == false)
    { // p2's turn
        if ((posX == 3 || posX == 4) && posY == 0)
        { // p1's server ports
            curOpponent->downloadLink(curPlayer->getLink(id));
        }
        else if ((posY == -1) && posX != 3 && posX != 4)
        { // p1's download edge
            curPlayer->downloadLink(curPlayer->getLink(id));
        }
        else if ((posX == 3 || posX == 4) && posY == 7)
        { // own server port!?
            curPlayer->moveLink(id, oppDir, whoseTurn);
            throw logic_error {"You can't move your link onto your own Server Port"};
        }
        else if (posX > 7 || posY > 7 || posX < 0 || posY < 0)
        { // off the map!!?
            curPlayer->moveLink(id, oppDir, whoseTurn);
            throw logic_error {"You can't move your link off the board"};
        }
    }

    // if it lands on other player's firewall
    if ((whoseTurn == true && b->getCell(posY, posX)->isPlayerTwoFirewall()) ||
            (whoseTurn == false && b->getCell(posY, posX)->isPlayerOneFirewall()))
    {
        curPlayer->getLink(id).reveal();
        if (curPlayer->getLink(id).checkIfData() == false)
        {
            curPlayer->downloadLink(curPlayer->getLink(id));
        }
        b->theBoard[posY][posX].setState(id);
    }

    // if it lands on other player's link = BATTLE!!
    // the only cell states left should be '.' and '[link]'
    if (b->getCell(posY, posX)->getState() != '.')
    {
        // at this point, it should be certain that the cell's state is the other player's link
        int curLinkLevel = curPlayer->getLink(id).getStrength();
        int oppLinkLevel = curOpponent->getLink(b->getCell(posY, posX)->getState()).getStrength();
        curPlayer->getLink(id).reveal();
        curOpponent->getLink(b->getCell(posY, posX)->getState()).reveal();

        if (curLinkLevel >= oppLinkLevel)
        { // if curPlayer wins
            curPlayer->downloadLink(curOpponent->getLink(b->getCell(posY, posX)->getState()));
            b->theBoard[posY][posX].setState(id);
        }
        else
        { // if curOpponent wins
            curOpponent->downloadLink(curPlayer->getLink(id));
        }
    }

    else
    cout << "normal move case";
    { // lands on an empty cell: '.'
        b->theBoard[posY][posX].setState(id);
    }
} // moveLink

void Game::printAbilities()
{
    Player *curPlayer = theirTurn(whoseTurn);
    curPlayer->printAbilities();
} // printAbilities


void Game::enableGD() {
    GDEnabled = true;
}


bool Game::isGDEnabled() {
    return GDEnabled;
}


std::ostream &operator<<(std::ostream &out, const Game &g)
{
    out << "\nPlayer 1:" << endl;
    out << "Downloaded: " << g.p1->getNumData() << "D, " << g.p1->getNumVirus() << "V" << endl;
    out << "Abilities: " << g.p1->getNumAbilities() << endl;
    // printLinks
    out << "========" << endl;
    if (g.b)
    {                  // Check if the smart pointer actually points to an object
        out << *(g.b); // Dereference the smart pointer to get the Board object
    }
    else
    {
        out << "Board not initialized.";
    }
    out << "========" << endl;
    out << "Player 2:" << endl;
    out << "Downloaded: " << g.p1->getNumData() << "D, " << g.p1->getNumVirus() << "V" << endl;
    out << "Abilities: " << g.p1->getNumAbilities() << endl << endl;;
    // printLinks
    return out;
}
