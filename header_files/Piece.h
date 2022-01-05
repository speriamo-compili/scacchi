#ifndef PIECE_H
#define PIECE_H
#include "Cell.h"
#include <fstream>

class Piece {
    public:
        enum colour {white, black};
        
        Piece(colour c);
        virtual ~Piece() {};

        virtual bool isValidMove(Cell& start_cell, Cell& end_cell) const = 0;
        virtual ostream& print_piece(ostream& of) const = 0;

        colour getPieceColour() const;
    private:
        colour pieceColour;
};

ostream& operator<<(ostream& of, const Piece& p);

#endif