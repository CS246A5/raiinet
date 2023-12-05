#ifndef _LINK_H_
#define _LINK_H_
#include <iostream>
#include <string>

class Link {
    int posX; // x-coordinate
    int posY; // y-coordinate
    int strength; // strength of the link, 1-4 (or up to 6 because of strength boost!)
    bool isRevealed = false; // true if the opponent has discovered this link
    bool isData; // true if this link is a data, false if it isn't
    bool isBoosted = false; // true if this link is boosted
    bool isSabotaged = false; // true if this link is sabotaged for its owner's turn
    bool isDownloaded = false; //true if this link is downloadedwhen

    public:
        Link();
        Link(int posX, int posY, int strength, bool isData);
        ~Link();
        int getPosX(); // returns the x-coordinate
        int getPosY(); // returns the y-coordinate
        void setPosX(int x); // updates the x-coordinate
        void setPosY(int y); // updates the y-coordinate
        int getStrength(); // returns the strength
        void setStrength(int s); //updates the strength
        bool checkIfRevealed(); // returns true if the opponent has discovered this link
        bool checkIfData(); // returns true if data
        bool checkIfBoosted(); // returns true if boosted
        // should check if boosted. If boosted, then move by 2 units. If not, then move 1
        bool checkIfSabotaged(); // returns true if sabotaged for its owner's turn
        bool checkIfDownloaded(); // returns true if downlaoded
        void setIsData(bool value); // Method to set the isData attribute
        void setIsDownloaded(bool value); //Method to set the isDownloaded attribute
        void setIsBoosted(bool value); // Method to set the isBoosted attribute
        void setIsSabotaged(bool value); // Method to set isSabotaged attribute
        void reveal(); // Method to set isRevealed to true
        void moveN(int); // move north
        void moveE(int); // move east
        void moveS(int); // move south
        void moveW(int); // move west
};

#endif
