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

        bool is_valid_move(Cell& start_cell, Cell& end_cell, Chessboard& board) const override;
        ostream& print_piece(ostream& of) const override;
        char get_letter() const override;
};

#endif