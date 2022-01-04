#include "..\header_files\Queen.h"

Queen::Queen(colour& c) : Piece(c) {};

bool Queen::isValidMove(Cell& start_cell, Cell& end_cell) const {
   // TO DO
   return true;
}

char Queen::print_piece() const {
   return getPieceColour() == white ? tolower(QUEEN_LETTER) : toupper(QUEEN_LETTER); 
}