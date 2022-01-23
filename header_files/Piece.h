/**
 * @file Piece.h
 * @author Simone Corrò
 */

#ifndef PIECE_H
#define PIECE_H

#include "Chessboard.h"
#include "Cell.h"

#include <fstream>

enum class Colour : short {white, black};

class Piece {
    public:
        Piece(Colour c, unsigned int id);
        virtual ~Piece() {};

        virtual bool is_valid_move(Cell& start_cell, Cell& end_cell, Chessboard& board) const = 0;
        virtual ostream& print_piece(ostream& of) const = 0;

        Colour get_colour() const;
        unsigned int get_id() const;
        virtual char get_letter() const = 0;
        bool are_cells_valid(Cell& start_cell, Cell& end_cell, Chessboard& board) const;

    private:
        Colour piece_colour;
        unsigned int _id;
};

ostream& operator<<(ostream& of, const Piece& p);
ostream& operator<<(ostream& of, const Colour& c);

#endif