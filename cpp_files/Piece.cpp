#include "..\header_files\Piece.h"

Piece::Piece(colour c) : pieceColour(c) {};

Piece::colour Piece::getPieceColour() const { 
    return pieceColour; 
}

ostream& operator<<(ostream& of, const Piece& p) {
    return p.print_piece(of); 
}