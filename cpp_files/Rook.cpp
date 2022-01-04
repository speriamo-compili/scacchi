#include "..\header_files\Rook.h"

Rook::Rook(colour& c) : Piece(c) {};

bool Rook::isValidMove(Cell& start_cell, Cell& end_cell) const {
   // TO DO
   return true;
}

char Rook::print_piece() const {
   return getPieceColour() == white ? tolower(ROOK_LETTER) : toupper(ROOK_LETTER); 
}