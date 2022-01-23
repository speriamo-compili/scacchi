/**
 * @file Bishop.h
 * @author Simone Corrò
 */

#ifndef BISHOP_H
#define BISHOP_H

#include "Piece.h"

class Bishop : public Piece {
    public: 
        const char BISHOP_LETTER = 'A';

        Bishop(Colour c, unsigned int id);
        ~Bishop() {};
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