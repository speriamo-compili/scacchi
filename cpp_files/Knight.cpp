#include "..\header_files\Knight.h"

Knight::Knight(colour& c) : Piece(c) {};

bool Knight::isValidMove(Cell& start_cell, Cell& end_cell) const {
   // TO DO
   return true;
}

char Knight::print_piece() const {
   return getPieceColour() == white ? tolower(KNIGHT_LETTER) : toupper(KNIGHT_LETTER); 
}