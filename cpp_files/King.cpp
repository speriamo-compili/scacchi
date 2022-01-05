#include "..\header_files\King.h"

King::King(colour c) : Piece(c) {};

bool King::isValidMove(Cell& start_cell, Cell& end_cell) const {
   int delta_row = start_cell.getRow() - end_cell.getRow();
   int delta_col = start_cell.getCol() - end_cell.getCol();

   bool valid_row = -1 <= delta_row && delta_row <= 1;
   bool valid_col = -1 <= delta_col && delta_col <= 1;
   
   return !(delta_row == 0 && delta_col == 0) && valid_row && valid_col;
}

ostream& King::print_piece(ostream& of) const {
   char c = getPieceColour() == white ? tolower(KING_LETTER) : toupper(KING_LETTER);
   of << c; 
   return of;
}