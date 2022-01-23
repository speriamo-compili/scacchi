/**
 * @file Pawn.h
 * @author Samuel Piron
 */

#ifndef PAWN_H
#define PAWN_H

#include "Piece.h"

class Pawn : public Piece {
    private:
        bool _has_moved;
        
    public:
        const char PAWN_LETTER = 'P';
        
        Pawn(Colour c, unsigned int id);
        ~Pawn() {};

        //check if the move from start cell to end cell is valid
        bool is_valid_move(Cell& start_cell, Cell& end_cell, Chessboard& board) const override;
        std::ostream& print_piece(std::ostream& of) const override;
        char get_letter() const override;
        bool has_moved() const; //check if it has moved
        void set_has_moved(bool b);
};

#endif