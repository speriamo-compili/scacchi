/**
 * @file Knight.h
 * @author Samuel Piron
 */

#ifndef KNIGHT_H
#define KNIGHT_H

#include "Piece.h"

class Knight : public Piece {
    public:
        const char KNIGHT_LETTER = 'C';

        Knight(Colour c, unsigned int id);
        ~Knight() {};

        bool is_valid_move(Cell& start_cell, Cell& end_cell, Chessboard& board) const override;
        std::ostream& print_piece(std::ostream& of) const override;
        char get_letter() const override;
};

#endif