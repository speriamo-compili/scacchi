#include "..\header_files\Bishop.h"

Bishop::Bishop(Colour c, unsigned int id) : Piece(c, id) {};

bool Bishop::isValidMove(Cell& start_cell, Cell& end_cell, Chessboard& board) const {
   if (start_cell == end_cell) {
      return false;
   }

   unsigned int start_row = start_cell.getRow(), start_col = start_cell.getCol();
   unsigned int end_row = end_cell.getRow(), end_col = end_cell.getCol();
   
   unsigned int min_row = min(start_row, end_row), max_row = max(start_row, end_row);
   unsigned int min_col = min(start_col, end_col), max_col = max(start_col, end_col);

   if (start_row - start_col == end_row - end_col) {
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

ostream& Bishop::print_piece(ostream& of) const {
   char c = getPieceColour() == Colour::white ? tolower(BISHOP_LETTER) : toupper(BISHOP_LETTER);
   of << c; 
   return of;
}