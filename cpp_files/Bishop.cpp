#include "..\header_files\Bishop.h"

Bishop::Bishop(colour c) : Piece(c) {};

bool Bishop::isValidMove(Cell& start_cell, Cell& end_cell) const {
   // TO DO
   return true;
}

ostream& Bishop::print_piece(ostream& of) const {
   char c = getPieceColour() == white ? tolower(BISHOP_LETTER) : toupper(BISHOP_LETTER);
   of << c; 
   return of;
}