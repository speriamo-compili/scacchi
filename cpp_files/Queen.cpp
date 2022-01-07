#include "..\header_files\Queen.h"

Queen::Queen(Colour c) : Piece(c) {};

bool Queen::isValidMove(Cell& start_cell, Cell& end_cell, Chessboard& board) const {
   // TO DO
   return true;
}

ostream& Queen::print_piece(ostream& of) const {
   char c = getPieceColour() == Colour::white ? tolower(QUEEN_LETTER) : toupper(QUEEN_LETTER);
   of << c; 
   return of;
}