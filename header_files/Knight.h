#ifndef KNIGHT_H
#define KNIGHT_H
#include "Piece.h"

class Knight : public Piece {
    public:
        const char KNIGHT_LETTER = 'C';

        Knight(colour& c);
        ~Knight() {};

        bool isValidMove(Cell& start_cell, Cell& end_cell) const override;
        char print_piece() const override;
};

#endif