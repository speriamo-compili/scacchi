#include "..\header_files\King.h"

King::King(colour& c) : Piece(c) {};

bool King::isValidMove(Cell& start_cell, Cell& end_cell) const {
   // TO DO
   return true;
}

char King::print_piece() const {
   return getPieceColour() == white ? tolower(KING_LETTER) : toupper(KING_LETTER); 
}