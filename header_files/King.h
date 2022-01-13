#ifndef KING_H
#define KING_H
#include "Piece.h"

class King : public Piece {
    private:
        bool _hasMoved;
        
    public:
        const char KING_LETTER = 'R';

        King(Colour c, unsigned int id);
        ~King() {};

        bool isValidMove(Cell& start_cell, Cell& end_cell, Chessboard& board) const override;
        ostream& print_piece(ostream& of) const override;
        char getLetter() const override;
        bool hasMoved() const;
        void set_has_moved(bool b);
};

#endif