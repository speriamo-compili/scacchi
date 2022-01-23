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
        /*
            check that the move is valid, the move is valid even if there is an opponent's piece in the arrival cell
        */
        virtual bool is_valid_move(Cell& start_cell, Cell& end_cell, Chessboard& board) const = 0;
        virtual std::ostream& print_piece(std::ostream& of) const = 0;
        /*
            returns the color of the piece
        */
        Colour get_colour() const;
        /*
            returns the id of the piece
        */
        unsigned int get_id() const;
        /* 
            returns the value of the constant (the initial of the piece)
        */        
        virtual char get_letter() const = 0;
        /*
            check if the starting cell has a player's piece to move and that the one in the final cell is the opponent's
        */
        bool are_cells_valid(Cell& start_cell, Cell& end_cell, Chessboard& board) const;

    private:
        Colour piece_colour;
        /*
            number that identifies a piece
        */
        unsigned int _id;
};

std::ostream& operator<<(std::ostream& of, const Piece& p);
std::ostream& operator<<(std::ostream& of, const Colour& c);

#endif