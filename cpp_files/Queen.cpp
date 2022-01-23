/**
 * @file Queen.cpp
 * @author Simone Corrò
 */

#include "../header_files/Queen.h"

Queen::Queen(Colour c, unsigned int id) : Piece(c, id) {};

bool Queen::is_valid_move(Cell& start_cell, Cell& end_cell, Chessboard& board) const {
   if (!are_cells_valid(start_cell, end_cell, board)) {
      return false;
   }
   
   unsigned int start_row = start_cell.get_row(), start_col = start_cell.get_col();
   unsigned int end_row = end_cell.get_row(), end_col = end_cell.get_col();

   unsigned int min_row = min(start_row, end_row), max_row = max(start_row, end_row);
   unsigned int min_col = min(start_col, end_col), max_col = max(start_col, end_col);
   
   if (start_row == end_row) {   
      for (unsigned int c = min(start_col, end_col) + 1; c < max(start_col, end_col); c++) {
         if (board.get_piece(Cell{start_row, c})) {
            return false;
         }
      }
      return true;
   } else if (start_col == end_col) {
      for (unsigned int r = min(start_row, end_row) + 1; r < max(start_row, end_row); r++) {
         if (board.get_piece(Cell{r, start_col})) {
            return false;
         }
      }
      return true;
   } else if (start_row - start_col == end_row - end_col) {
      for (unsigned int r = min_row + 1, c = min_col + 1; r < max_row && c < max_col; r++, c++) {
         if (board.get_piece(Cell{r,c})) {
            return false;
         }
      }
      return true;
   } else if (start_row + start_col == end_row + end_col) {
      for (unsigned int r = min_row + 1, c = max_col - 1; r < max_row && c > min_col; r++, c--) {
         if (board.get_piece(Cell{r,c})) {
            return false;
         }
      }
      return true;
   }

   return false;
}

ostream& Queen::print_piece(ostream& of) const {
   char c = get_colour() == Colour::white ? tolower(QUEEN_LETTER) : toupper(QUEEN_LETTER);
   of << c; 
   return of;
}

char Queen::get_letter() const {
   return get_colour() == Colour::white ? tolower(QUEEN_LETTER) : toupper(QUEEN_LETTER);
}