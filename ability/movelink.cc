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

        cin >> id >> posX >> posY;
        try{
            Link& link = opponent.getLink(id);
            Player *curPlayer = &player;
            Player *curOpponent = &opponent;

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
                link.setPosX(posX);
                link.setPosY(posY);
                setUsed(true);
                b->changeState(posX, posY, id);
            } else {
                cout << "Position is illegal please re-enter id, poition X and Y: ";
            }
        } catch (const std::runtime_error& e) {
             // Specified link is not found
            cout << "Link not found. Please re-enter the link name, posX and posY: ";
        }
    }  
}





