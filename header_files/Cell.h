#ifndef CELL_H
#define CELL_H
#include <iostream>
using namespace std;

class Cell {
    private:
        // row and col are 0-based, they're in the range [0,7]
        unsigned int row, col;

        bool is_valid_col(char& c) const;
        bool is_valid_row(char& r) const;
        unsigned int get_index_col(char& c) const;
        unsigned int get_index_row(char& r) const;

    public:
        class invalid_cell{};
        static const unsigned int LENGTH_STRING_OF_A_CELL = 2;
        static const unsigned int MAX_ROWS_COLS = 8;

        Cell();
        Cell(unsigned int r, unsigned int c);
        Cell(string s);
        unsigned int get_row() const;
        unsigned int get_col() const;
        ~Cell() {};
};

bool operator==(const Cell &a, const Cell &b);
bool operator!=(const Cell &a, const Cell &b);
ostream& operator<< (ostream& os, Cell& c);
#endif