/**
 * @file Rook.cpp
 * @author Samuel Piron
 */

#include "../header_files/Rook.h"

Rook::Rook(Colour c, unsigned int id) : Piece(c, id), _has_moved{false} {};
//it checks if the rook can move from start cell to end cell
bool Rook::is_valid_move(Cell& start_cell, Cell& end_cell, Chessboard& board) const {
   if (!are_cells_valid(start_cell, end_cell, board)) {
      return false;
   }
   
   unsigned int start_row = start_cell.get_row(), start_col = start_cell.get_col();
   unsigned int end_row = end_cell.get_row(), end_col = end_cell.get_col();

   if (start_row == end_row) {   
      for (unsigned int c = std::min(start_col, end_col) + 1; c < std::max(start_col, end_col); c++) {
         if (board.get_piece(Cell{start_row, c})) {
            return false;
         }
      }
      return true;
   } else if (start_col == end_col) {
      for (unsigned int r = std::min(start_row, end_row) + 1; r < std::max(start_row, end_row); r++) {
         if (board.get_piece(Cell{r, start_col})) {
            return false;
         }
      }
      return true;
   }
   return false;
}
//it prints the piece
std::ostream& Rook::print_piece(std::ostream& of) const {
   char c = get_colour() == Colour::white ? tolower(ROOK_LETTER) : toupper(ROOK_LETTER);
   of << c; 
   return of;
}
//it returns letter of the rook
char Rook::get_letter() const {
   return get_colour() == Colour::white ? tolower(ROOK_LETTER) : toupper(ROOK_LETTER);
}

bool Rook::has_moved() const {
   return _has_moved;
}

void Rook::set_has_moved(bool b) {
   _has_moved = b;
}