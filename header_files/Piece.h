#ifndef PIECE_H
#define PIECE_H
#include "Cell.h"

class Piece {
    public:
        enum colour {white, black};
        
        Piece(colour& c);
        virtual ~Piece() {};

        virtual bool isValidMove(Cell& start_cell, Cell& end_cell) const = 0;
        virtual char print_piece() const = 0;

        colour getPieceColour() const;
    private:
        colour pieceColour;
};

#endif