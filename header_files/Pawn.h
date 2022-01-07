#ifndef PAWN_H
#define PAWN_H
#include "Piece.h"

class Pawn : public Piece {
    public:
        const char PAWN_LETTER = 'P';
        
        Pawn(Colour c);
        ~Pawn() {};

        bool isValidMove(Cell& start_cell, Cell& end_cell, Chessboard& board) const override;
        ostream& print_piece(ostream& of) const override;
};

#endif