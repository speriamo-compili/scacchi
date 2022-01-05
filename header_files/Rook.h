#ifndef ROOK_H
#define ROOK_H
#include "Piece.h"

class Rook : public Piece {
    public:
        const char ROOK_LETTER = 'T';
                
        Rook(colour c);
        ~Rook() {};

        bool isValidMove(Cell& start_cell, Cell& end_cell) const override;
        ostream& print_piece(ostream& of) const override;
};

#endif