#include "..\header_files\Cell.h"

// check if s represent the coordinate of chessboard's cell
Cell::Cell(string& s) {
    if (s.size() != Cell::LENGTH_STRING_OF_A_CELL) {
        throw InvalidCell();
    }
    
    char c = toupper(s[0]), r = s[1];
    if(!isValidCol(c) || !isValidRow(r)) {
        throw InvalidCell();
    } 

    row = getIndexRow(r);
    col = getIndexCol(c);
}

// c is UPPER_CASE
bool Cell::isValidCol(char& c) const {
    return 'A' <= c && c <= 'H'; 
}

bool Cell::isValidRow(char& r) const {
    return '1' <= r && r <= '8'; 
}

// c is UPPER_CASE
unsigned int Cell::getIndexCol(char& c) const {
    return c - 'A';
}

unsigned int Cell::getIndexRow(char& r) const {
    return r - '1';
}

unsigned int Cell::getRow() const {
    return row;
}

unsigned int Cell::getCol() const {
    return col;
}