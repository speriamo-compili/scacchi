#ifndef PIECE_H
#define PIECE_H
#include "Chessboard.h"
#include "Cell.h"
#include <fstream>

enum class Colour {white, black};

class Piece {
    public:
        Piece(Colour c, unsigned int id);
        virtual ~Piece() {};

        virtual bool isValidMove(Cell& start_cell, Cell& end_cell, Chessboard& board) const = 0;
        virtual ostream& print_piece(ostream& of) const = 0;

        Colour getColour() const;
        unsigned int getId() const;
        virtual char getLetter() const = 0;
        bool areCellsValid(Cell& start_cell, Cell& end_cell, Chessboard& board) const;

    private:
        Colour pieceColour;
        unsigned int _id;
};

ostream& operator<<(ostream& of, const Piece& p);

#endif