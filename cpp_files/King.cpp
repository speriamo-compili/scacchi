#include "../header_files/King.h"

King::King(Colour c, unsigned int id) : Piece(c, id), _has_moved{false} {};

bool King::is_valid_move(Cell& start_cell, Cell& end_cell, Chessboard& board) const {
   if (!are_cells_valid(start_cell, end_cell, board)) {
      return false;
   }
   
   int delta_row = start_cell.get_row() - end_cell.get_row();
   int delta_col = start_cell.get_col() - end_cell.get_col();

   bool valid_row = -1 <= delta_row && delta_row <= 1;
   bool valid_col = -1 <= delta_col && delta_col <= 1;
   
   return !(delta_row == 0 && delta_col == 0) && valid_row && valid_col;
}

ostream& King::print_piece(ostream& of) const {
   char c = get_colour() == Colour::white ? tolower(KING_LETTER) : toupper(KING_LETTER);
   of << c; 
   return of;
}

char King::get_letter() const {
   return get_colour() == Colour::white ? tolower(KING_LETTER) : toupper(KING_LETTER);
}

bool King::has_moved() const {
   return _has_moved;
}

void King::set_has_moved(bool b) {
   _has_moved = b;
}
