#include "..\header_files\Rook.h"

Rook::Rook(Colour c) : Piece(c) {};

bool Rook::isValidMove(Cell& start_cell, Cell& end_cell, Chessboard& board) const {
   unsigned int start_row = start_cell.getRow(), start_col = start_cell.getCol();
   unsigned int end_row = end_cell.getRow(), end_col = end_cell.getCol();

   if (start_row == end_row && start_col != end_col) {   
      for (unsigned int c = min(start_col, end_col) + 1; c < max(start_col, end_col); c++) {
         if (board.getPiece(Cell{start_row, c})) {
            return false;
         }
      }
      return true;
   } else if (start_col == end_col && start_row != end_row) {
      for (unsigned int r = min(start_row, end_row) + 1; r < max(start_row, end_row); r++) {
         if (board.getPiece(Cell{r, start_col})) {
            return false;
         }
      }
      return true;
   }
   return false;
}

ostream& Rook::print_piece(ostream& of) const {
   char c = getPieceColour() == Colour::white ? tolower(ROOK_LETTER) : toupper(ROOK_LETTER);
   of << c; 
   return of;
}