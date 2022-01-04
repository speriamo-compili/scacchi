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

        Cell(string& s);
        unsigned int getRow() const;
        unsigned int getCol() const;
        ~Cell() {};
};

#endif