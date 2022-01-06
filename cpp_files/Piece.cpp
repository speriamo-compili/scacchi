#include "..\header_files\Piece.h"

Piece::Piece(Colour c) : pieceColour(c) {};

Colour Piece::getPieceColour() const { 
    return pieceColour; 
}

ostream& operator<<(ostream& of, const Piece& p) {
    return p.print_piece(of); 
}