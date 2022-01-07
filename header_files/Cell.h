#ifndef CELL_H
#define CELL_H
#include <iostream>
using namespace std;

class Cell {
    private:
        // row and col are 0-based, they're in the range [0,7]
        unsigned int row, col;

        bool isValidCol(char& c) const;
        bool isValidRow(char& r) const;
        unsigned int getIndexCol(char& c) const;
        unsigned int getIndexRow(char& r) const;

    public:
        class InvalidCell{}; // REMINDER: decide if it's the right place for exceptions
        const unsigned int LENGTH_STRING_OF_A_CELL = 2;
        const unsigned int MAX_ROWS_COLS = 8;

        Cell(unsigned int r, unsigned int c);
        Cell(string& s);
        unsigned int getRow() const;
        unsigned int getCol() const;
        ~Cell() {};
};

bool operator==(const Cell &a, const Cell &b);
bool operator!=(const Cell &a, const Cell &b);
#endif