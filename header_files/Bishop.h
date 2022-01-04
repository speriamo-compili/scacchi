#ifndef BISHOP_H
#define BISHOP_H
#include "Piece.h"

class Bishop : public Piece {
    public: 
        const char BISHOP_LETTER = 'A';

        Bishop(colour& c);
        ~Bishop() {};

        bool isValidMove(Cell& start_cell, Cell& end_cell) const override;
        char print_piece() const override;
};

#endif