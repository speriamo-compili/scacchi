#include "..\header_files\Rook.h"

Rook::Rook(colour c) : Piece(c) {};

bool Rook::isValidMove(Cell& start_cell, Cell& end_cell) const {
   int delta_row = start_cell.getRow() - end_cell.getRow();
   int delta_col = start_cell.getCol() - end_cell.getCol();  
   
   if (delta_row != 0 && delta_col != 0)
      return false;

   return false;
}

ostream& Rook::print_piece(ostream& of) const {
   char c = getPieceColour() == white ? tolower(ROOK_LETTER) : toupper(ROOK_LETTER);
   of << c; 
   return of;
}