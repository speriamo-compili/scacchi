#include "..\header_files\Piece.h"

Piece::Piece(Colour c, unsigned int id) : pieceColour(c), _id{id} {};

Colour Piece::getPieceColour() const { 
    return pieceColour; 
}

ostream& operator<<(ostream& of, const Piece& p) {
    return p.print_piece(of); 
}