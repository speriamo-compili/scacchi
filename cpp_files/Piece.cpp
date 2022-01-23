/**
 * @file Piece.cpp
 * @author Simone Corrò
 */

#include "../header_files/Piece.h"

Piece::Piece(Colour c, unsigned int id) : piece_colour(c), _id{id} {};

Colour Piece::get_colour() const { 
    return piece_colour; 
}

unsigned int Piece::get_id() const {
    return _id;
}

bool Piece::are_cells_valid(Cell& start_cell, Cell& end_cell, Chessboard& board) const {
    if (start_cell == end_cell) {
        return false;
    }
    Piece *piece_to_move = board.get_piece(start_cell);
    if (!piece_to_move) {
        return false;
    }
    Piece *piece_end_cell = board.get_piece(end_cell);
    return !piece_end_cell || piece_to_move->get_colour() != piece_end_cell->get_colour();
}

ostream& operator<<(ostream& of, const Piece& p) {
    return p.print_piece(of); 
}

ostream& operator<<(ostream& of, const Colour& c) {
    of << (c == Colour::white ? "white" : "black");
    return of;
}