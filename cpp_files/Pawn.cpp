#include "..\header_files\Pawn.h"

Pawn::Pawn(colour& c) : Piece(c) {};

bool Pawn::isValidMove(Cell& start_cell, Cell& end_cell) const {
   // TO DO
   return true;
}

char Pawn::print_piece() const {
   return getPieceColour() == white ? tolower(PAWN_LETTER) : toupper(PAWN_LETTER); 
}