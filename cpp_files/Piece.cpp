#include "..\header_files\Piece.h"

Piece::Piece(Colour c, unsigned int id) : pieceColour(c), _id{id} {};

Colour Piece::getColour() const { 
    return pieceColour; 
}

unsigned int Piece::getId() const {
    return _id;
}

ostream& operator<<(ostream& of, const Piece& p) {
    return p.print_piece(of); 
}