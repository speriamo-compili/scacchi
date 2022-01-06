#include "..\header_files\Knight.h"

Knight::Knight(Colour c) : Piece(c) {};

bool Knight::isValidMove(Cell& start_cell, Cell& end_cell) const {
   // TO DO
   return true;
}

ostream& Knight::print_piece(ostream& of) const {
   char c = getPieceColour() == Colour::white ? tolower(KNIGHT_LETTER) : toupper(KNIGHT_LETTER);
   of << c; 
   return of;
}