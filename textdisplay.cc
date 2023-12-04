#include "textdisplay.h"

using namespace std;

TextDisplay::TextDisplay() {
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            theDisplay[i][j] = '.';
        }
    }
}

TextDisplay::~TextDisplay() {}

void TextDisplay::notify(Cell &c) {
    theDisplay[c.getRow()][c.getColumn()] = c.getState();
}

std::ostream &operator<<(std::ostream &out, const TextDisplay &td) {
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            out << td.theDisplay[i][j];
        }
        out << endl;
    }
    return out;
}

