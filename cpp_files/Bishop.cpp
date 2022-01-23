/**
 * @file Bishop.cpp
 * @author Simone Corrò
 */

#include "../header_files/Bishop.h"

Bishop::Bishop(Colour c, unsigned int id) : Piece(c, id) {};

bool Bishop::is_valid_move(Cell& start_cell, Cell& end_cell, Chessboard& board) const {
   if (!are_cells_valid(start_cell, end_cell, board)) {
      return false;
   }

   unsigned int start_row = start_cell.get_row(), start_col = start_cell.get_col();
   unsigned int end_row = end_cell.get_row(), end_col = end_cell.get_col();
   
   unsigned int min_row = std::min(start_row, end_row), max_row = std::max(start_row, end_row);
   unsigned int min_col = std::min(start_col, end_col), max_col = std::max(start_col, end_col);

   if (start_row - start_col == end_row - end_col) {
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

std::ostream& Bishop::print_piece(std::ostream& of) const {
   char c = get_colour() == Colour::white ? tolower(BISHOP_LETTER) : toupper(BISHOP_LETTER);
   of << c; 
   return of;
}

char Bishop::get_letter() const {
   return get_colour() == Colour::white ? tolower(BISHOP_LETTER) : toupper(BISHOP_LETTER);
}