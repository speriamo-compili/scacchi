/**
 * @file Pawn.cpp
 * @author Samuel Piron
 */

#include "../header_files/Pawn.h"

Pawn::Pawn(Colour c, unsigned int id) : Piece(c, id), _has_moved{false} {};

bool Pawn::is_valid_move(Cell& start_cell, Cell& end_cell, Chessboard& board) const {
   if (!are_cells_valid(start_cell, end_cell, board)) {
      return false;
   }
   
   unsigned int start_row = start_cell.get_row(), start_col = start_cell.get_col();
   unsigned int end_row = end_cell.get_row(), end_col = end_cell.get_col();

   if (get_colour() == Colour::white) {
      if (board.get_piece(end_cell)) {
         // if there is a piece, it has to move diagonally
         return start_row + 1 == end_row && (start_col + 1 == end_col || start_col - 1 == end_col);
      } else {
         // if there isn't a piece, it has to move forward of one or two cell
         bool one_step = start_row + 1 == end_row;
         bool two_steps = !has_moved() && start_row + 2 == end_row && !board.get_piece(Cell{start_row + 1, end_col});
         return start_col == end_col && (one_step || two_steps);
      }
   } else {
      if (board.get_piece(end_cell)) {
         // if there is a piece, it has to move diagonally
         return start_row - 1 == end_row && (start_col + 1 == end_col || start_col - 1 == end_col);
      } else {
         // if there isn't a piece, it has to move forward of one or two cell
         bool one_step = start_row - 1 == end_row;
         bool two_steps = !has_moved() && start_row - 2 == end_row && !board.get_piece(Cell{start_row - 1, end_col});
         return start_col == end_col && (one_step || two_steps);      
      }
   }
   
   return false;
}

std::ostream& Pawn::print_piece(std::ostream& of) const {
   char c = get_colour() == Colour::white ? tolower(PAWN_LETTER) : toupper(PAWN_LETTER);
   of << c; 
   return of;
}
//it return the letter of the pawn
char Pawn::get_letter() const {
   return get_colour() == Colour::white ? tolower(PAWN_LETTER) : toupper(PAWN_LETTER);
}

bool Pawn::has_moved() const {
   return _has_moved;
}
//set new has moved
void Pawn::set_has_moved(bool b) {
   _has_moved = b;
}