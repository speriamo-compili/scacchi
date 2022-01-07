#ifndef QUEEN_H
#define QUEEN_H
#include "Piece.h"

class Queen : public Piece {
    public:
        const char QUEEN_LETTER = 'D';
        
        Queen(Colour c);
        ~Queen() {};

        bool isValidMove(Cell& start_cell, Cell& end_cell, Chessboard& board) const override;
        ostream& print_piece(ostream& of) const override;
};

#endif