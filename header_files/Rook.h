/**
 * @file Rook.h
 * @author Samuel Piron
 */

#ifndef ROOK_H
#define ROOK_H

#include "Piece.h"

class Rook : public Piece {
    private:
        bool _has_moved;
        
    public:
        const char ROOK_LETTER = 'T';
                
        Rook(Colour c, unsigned int id);
        ~Rook() {};
        //check if the move from start cell to end cell is valid
        bool is_valid_move(Cell& start_cell, Cell& end_cell, Chessboard& board) const override;
        std::ostream& print_piece(std::ostream& of) const override;
        char get_letter() const override;
        bool has_moved() const; //check if it has moved
        void set_has_moved(bool b);
};

#endif