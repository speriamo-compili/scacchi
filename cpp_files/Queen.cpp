#include "..\header_files\Queen.h"

Queen::Queen(Colour c, unsigned int id) : Piece(c, id) {};

bool Queen::isValidMove(Cell& start_cell, Cell& end_cell, Chessboard& board) const {
   if (start_cell == end_cell) {
      return false;
   }
   
   unsigned int start_row = start_cell.getRow(), start_col = start_cell.getCol();
   unsigned int end_row = end_cell.getRow(), end_col = end_cell.getCol();

   unsigned int min_row = min(start_row, end_row), max_row = max(start_row, end_row);
   unsigned int min_col = min(start_col, end_col), max_col = max(start_col, end_col);
   
   if (start_row == end_row) {   
      for (unsigned int c = min(start_col, end_col) + 1; c < max(start_col, end_col); c++) {
         if (board.getPiece(Cell{start_row, c})) {
            return false;
         }
      }
      return true;
   } else if (start_col == end_col) {
      for (unsigned int r = min(start_row, end_row) + 1; r < max(start_row, end_row); r++) {
         if (board.getPiece(Cell{r, start_col})) {
            return false;
         }
      }
      return true;
   } else if (start_row - start_col == end_row - end_col) {
      for (unsigned int r = min_row + 1, c = min_col + 1; r < max_row && c < max_col; r++, c++) {
         if (board.getPiece(Cell{r,c})) {
            return false;
         }
      }
      return true;
   } else if (start_row + start_col == end_row + end_col) {
      for (unsigned int r = min_row + 1, c = max_col - 1; r < max_row && c > min_col; r++, c--) {
         if (board.getPiece(Cell{r,c})) {
            return false;
         }
      }
      return true;
   }

   return false;
}

ostream& Queen::print_piece(ostream& of) const {
   char c = getPieceColour() == Colour::white ? tolower(QUEEN_LETTER) : toupper(QUEEN_LETTER);
   of << c; 
   return of;
}