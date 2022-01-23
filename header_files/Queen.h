/**
 * @file Queen.h
 * @author Simone Corrò
 */

#ifndef QUEEN_H
#define QUEEN_H

#include "Piece.h"

class Queen : public Piece {
    public:
        const char QUEEN_LETTER = 'D';
        
        Queen(Colour c, unsigned int id);
        ~Queen() {};
        /*
            check that the move is valid, the move is valid even if there is an opponent's piece in the arrival cell
        */
        bool is_valid_move(Cell& start_cell, Cell& end_cell, Chessboard& board) const override;

        std::ostream& print_piece(std::ostream& of) const override;
        /* 
            returns the value of the constant (the initial of the piece)
        */
        char get_letter() const override;
};

#endif