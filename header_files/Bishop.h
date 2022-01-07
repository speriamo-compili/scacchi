#ifndef BISHOP_H
#define BISHOP_H
#include "Piece.h"

class Bishop : public Piece {
    public: 
        const char BISHOP_LETTER = 'A';

        Bishop(Colour c);
        ~Bishop() {};

        bool isValidMove(Cell& start_cell, Cell& end_cell, Chessboard& board) const override;
        ostream& print_piece(ostream& of) const override;
};

#endif