#include "..\header_files\Knight.h"

Knight::Knight(Colour c, unsigned int id) : Piece(c, id) {};

bool Knight::isValidMove(Cell& start_cell, Cell& end_cell, Chessboard& board) const {
   int delta_row = abs(static_cast<int>(start_cell.getRow()) - static_cast<int>(end_cell.getRow()));
   int delta_col = abs(static_cast<int>(start_cell.getCol()) - static_cast<int>(end_cell.getCol()));

   return (delta_row == 1 && delta_col == 2) || (delta_row == 2 && delta_col == 1);
}

ostream& Knight::print_piece(ostream& of) const {
   char c = getPieceColour() == Colour::white ? tolower(KNIGHT_LETTER) : toupper(KNIGHT_LETTER);
   of << c; 
   return of;
}