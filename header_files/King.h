#ifndef KING_H
#define KING_H
#include "Piece.h"

class King : public Piece {
    public:
        const char KING_LETTER = 'R';

        King(colour& c);
        ~King() {};

        bool isValidMove(Cell& start_cell, Cell& end_cell) const override;
        char print_piece() const override;
};

#endif