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

        bool is_valid_move(Cell& start_cell, Cell& end_cell, Chessboard& board) const override;
        ostream& print_piece(ostream& of) const override;
        char get_letter() const override;
        bool has_moved() const;
        void set_has_moved(bool b);
};

#endif