#include "..\header_files\Piece.h"

Piece::Piece(Colour c, unsigned int id) : pieceColour(c), _id{id} {};

Colour Piece::getColour() const { 
    return pieceColour; 
}

unsigned int Piece::getId() const {
    return _id;
}

bool Piece::areCellsValid(Cell& start_cell, Cell& end_cell, Chessboard& board) const {
    if (start_cell == end_cell) {
        return false;
    }
    Piece *piece_to_move = board.getPiece(start_cell);
    if (!piece_to_move) {
        return false;
    }
    Piece *piece_end_cell = board.getPiece(end_cell);
    return !piece_end_cell || piece_to_move->getColour() != piece_end_cell->getColour();
}

ostream& operator<<(ostream& of, const Piece& p) {
    return p.print_piece(of); 
}

ostream& operator<<(ostream& of, const Colour& c) {
    of << (c == Colour::white ? "white" : "black");
    return of;
}
