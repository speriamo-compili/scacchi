#include "..\header_files\Bishop.h"

Bishop::Bishop(colour& c) : Piece(c) {};

bool Bishop::isValidMove(Cell& start_cell, Cell& end_cell) const {
   // TO DO
   return true;
}

char Bishop::print_piece() const {
   return getPieceColour() == white ? tolower(BISHOP_LETTER) : toupper(BISHOP_LETTER); 
}