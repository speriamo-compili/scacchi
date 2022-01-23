#ifndef KING_H
#define KING_H
#include "Piece.h"

class King : public Piece {
    private:
        bool _has_moved;
        
    public:
        const char KING_LETTER = 'R';

        King(Colour c, unsigned int id);
        ~King() {};

        bool is_valid_move(Cell& start_cell, Cell& end_cell, Chessboard& board) const override;
        ostream& print_piece(ostream& of) const override;
        char get_letter() const override;
        bool has_moved() const;
        void set_has_moved(bool b);
};

#endif