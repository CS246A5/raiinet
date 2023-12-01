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

    public:
    Link(int posX, int posY, int strength, bool isData);
    ~Link();
    int getPosX(); // returns the x-coordinate
    int getPosY(); // returns the y-coordinate
    void setPosX(int x); // updates the x-coordinate
    void setPosY(int y); // updates the y-coordinate
    int getStrength(); // returns the strength
    bool checkIfRevealed(); // returns true if the opponent has discovered this link
    bool checkIfData(); // returns true if data
    bool checkIfBoosted(); // returns true if boosted
    bool checkIfSabotaged(); // returns true if sabotaged for its owner's turn
    void setIsData(bool value); // Method to set the isData attribute

    // should check if boosted. If boosted, then move by 2 units. If not, then move 1
    void moveN(); // move north
    void moveE(); // move east
    void moveS(); // move south
    void moveW(); // move west
};
