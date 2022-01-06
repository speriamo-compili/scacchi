#ifndef PIECE_H
#define PIECE_H
#include "Cell.h"
#include <fstream>

enum class Colour {white, black};

class Piece {
    public:
        Piece(Colour c);
        virtual ~Piece() {};

        virtual bool isValidMove(Cell& start_cell, Cell& end_cell) const = 0;
        virtual ostream& print_piece(ostream& of) const = 0;

        Colour getPieceColour() const;
    private:
        Colour pieceColour;
};

ostream& operator<<(ostream& of, const Piece& p);

#endif