/**
 * @file King.h
 * @author Simone Corrò
 */

#ifndef KING_H
#define KING_H

#include "Piece.h"

class King : public Piece {
    private:
        /*
            remember if the piece has already been moved
        */
        bool _has_moved;
        
    public:
        const char KING_LETTER = 'R';

        King(Colour c, unsigned int id);
        ~King() {};
        /*
            check that the move is valid, the move is valid even if there is an opponent's piece in the arrival cell
        */
        bool is_valid_move(Cell& start_cell, Cell& end_cell, Chessboard& board) const override;
        std::ostream& print_piece(std::ostream& of) const override;
        /* 
            returns the value of the constant (the initial of the piece)
        */
        char get_letter() const override;
        /*
            returns the value of the has_moved variable 
        */
        bool has_moved() const;
        /*
            set the has_moved variable
        */
        void set_has_moved(bool b);
};

#endif