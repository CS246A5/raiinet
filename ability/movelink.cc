#include "ability.h"
#include "../board.h"
#include "../player.h"
#include "../game.h"
#include "movelink.h"


//create constructor
MoveLink::MoveLink(): Ability("Move Link", move(theGame)) {}

//create destructor
MoveLink::~MoveLink() {}

//create activate
void MoveLink::activate(Player& player, Player& opponent ) { 
    // Read input to determine which link to download 
    char id;
    int posX;
    int posY;
    
    while (true) {
        Board *b = player.getGame()->getBoard(); 
        // grab the link that is getting moved
        Link *l;

        // read in id, col, row
        cin >> id >> posX >> posY;
        // case if the id does not exist
        if (!(id == 'a' || id == 'b' || id == 'c' || id == 'd' || 
                id == 'e' || id == 'f' || id == 'g' || id == 'h' || 
                id == 'A' || id == 'B' || id == 'C' || id == 'D' || 
                id == 'E' || id == 'F' || id == 'G' || id == 'H')) {
            throw logic_error {"This link id does not exist. Try again."};
        }
        else if ((id == 'a' || id == 'b' || id == 'c' || id == 'd' ||
                id == 'e' || id == 'f' || id == 'g' || id == 'h')) {
            l= &player.getGame()->theirTurn(true)->getPureLink(id);
        }
        else l = &player.getGame()->theirTurn(false)->getPureLink(id);

        bool illegalPos = false;

        // if was on firewall: // how to access board?
        if (b->theBoard[posX][posY].isPlayerOneFirewall()) {
            illegalPos = true;
        } 
        else if (b->theBoard[posX][posY].isPlayerTwoFirewall()) {
            illegalPos = true;
        }   else if (b->getCell(posY, posX)->getState() != '.')  {
            illegalPos = true;
        }

        //check if on server port or off the map
        if ((posX == 3 || posX == 4) && posY == 7) { 
            illegalPos = true;
        }
        else if ((posY == 8 && posX != 3 && posX != 4)) { 
            illegalPos = true;
        }
        else if ((posX == 3 || posX == 4) && posY == 0) {
            illegalPos = true;
        } else if ((posY == -1) && posX != 3 && posX != 4) { 
            illegalPos = true;
        }

        if(!illegalPos){
            l->setPosX(posX);
            l->setPosY(posY);
            setUsed(true);
            b->theBoard[posY][posX].setState(id);
            cout << "Link " << id << " has been moved to position (" 
                << posX << ", " << posY << ")." << endl;
            cout << *b;

        } else {
            throw logic_error {"Position is illegal. please re-enter id, position X and Y: "};
        }
    }
}





