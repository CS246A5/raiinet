#include "ability.h"
#include "strengthboost.h"

#include "../board.h"
#include "../player.h"
#include "../game.h"

//create constructor
StrengthBoost::StrengthBoost(): Ability("StrengthBoost", move(theGame)) {}

//create destructor
StrengthBoost::~StrengthBoost() {}

//create activate
void StrengthBoost::activate(Player& player, Player& opponent ) { 
    // Read input to determine which link to boost strength 
    //cout << "Enter the ID of the link you want to move: ";
    char id;
     while (true) {
        cin >> id;

        Link *l; // pointer to the link we strengthening
        if (player.getGame()->checkWhoseTurn() && (id == 'a' || id == 'b' || id == 'c' || id == 'd' ||
                id == 'e' || id == 'f' || id == 'g' || id == 'h')) {
            l = &player.getPureLink(id);
        }
        else if (!player.getGame()->checkWhoseTurn() && (id == 'A' || id == 'B' || id == 'C' || 
            id == 'D' || id == 'E' || id == 'F' || id == 'G' || id == 'H')) {
            l = &player.getPureLink(id);
        }
        else throw logic_error {"Invalid Id. Try again."};

        l->setStrength(l->getStrength() + 1);
        setUsed(true);
        cout << "Link " << id << " has been boosted in strength.\n";
        break; // Exit the loop since we found the link
    }
}







