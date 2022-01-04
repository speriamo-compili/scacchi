#include "..\header_files\Piece.h"

Piece::Piece(colour& c) : pieceColour(c) {};

Piece::colour Piece::getPieceColour() const { 
    return pieceColour; 
}