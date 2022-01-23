#include "../header_files/Cell.h"

Cell::Cell() {
    row = 0;
    col = 0;
}

Cell::Cell(unsigned int r, unsigned int c) {
    if (r >= MAX_ROWS_COLS && c >= MAX_ROWS_COLS) {
        throw invalid_cell();
    }
    row = r;
    col = c;
}

// check if s represent the coordinate of chessboard's cell
Cell::Cell(string s) {
    if (s.size() != Cell::LENGTH_STRING_OF_A_CELL) {
        throw invalid_cell();
    }
    
    char c = toupper(s[0]), r = s[1];
    if(!is_valid_col(c) || !is_valid_row(r)) {
        throw invalid_cell();
    } 

    row = get_index_row(r);
    col = get_index_col(c);
}

// c is UPPER_CASE
bool Cell::is_valid_col(char& c) const {
    return 'A' <= c && c <= 'H'; 
}

bool Cell::is_valid_row(char& r) const {
    return '1' <= r && r <= '8'; 
}

// c is UPPER_CASE
unsigned int Cell::get_index_col(char& c) const {
    return c - 'A';
}

unsigned int Cell::get_index_row(char& r) const {
    return r - '1';
}

unsigned int Cell::get_row() const {
    return row;
}

unsigned int Cell::get_col() const {
    return col;
}

bool operator==(const Cell &a, const Cell &b) {
    return a.get_row() == b.get_row() && a.get_col() == b.get_col();
}

bool operator!=(const Cell &a, const Cell &b) {
    return a.get_row() != b.get_row() || a.get_col() != b.get_col();
}

ostream& operator<< (ostream& os, Cell& c) {
    os << char('A' + c.get_col()) << c.get_row() + 1;
    return os;
}