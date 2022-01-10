#ifndef ROOK_H
#define ROOK_H
#include "Piece.h"

class Rook : public Piece {
    public:
        const char ROOK_LETTER = 'T';
                
        Rook(Colour c, unsigned int id);
        ~Rook() {};

        bool isValidMove(Cell& start_cell, Cell& end_cell, Chessboard& board) const override;
        ostream& print_piece(ostream& of) const override;
};

#endif