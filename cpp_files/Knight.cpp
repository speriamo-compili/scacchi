#include "../header_files/Knight.h"

Knight::Knight(Colour c, unsigned int id) : Piece(c, id) {};

bool Knight::is_valid_move(Cell& start_cell, Cell& end_cell, Chessboard& board) const {
   if (!are_cells_valid(start_cell, end_cell, board)) {
      return false;
   }
   
   int delta_row = abs(static_cast<int>(start_cell.get_row()) - static_cast<int>(end_cell.get_row()));
   int delta_col = abs(static_cast<int>(start_cell.get_col()) - static_cast<int>(end_cell.get_col()));

   return (delta_row == 1 && delta_col == 2) || (delta_row == 2 && delta_col == 1);
}

ostream& Knight::print_piece(ostream& of) const {
   char c = get_colour() == Colour::white ? tolower(KNIGHT_LETTER) : toupper(KNIGHT_LETTER);
   of << c; 
   return of;
}

char Knight::get_letter() const {
   return get_colour() == Colour::white ? tolower(KNIGHT_LETTER) : toupper(KNIGHT_LETTER);
}
