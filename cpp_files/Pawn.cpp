#include "..\header_files\Pawn.h"

Pawn::Pawn(Colour c, unsigned int id) : Piece(c, id), _hasMoved{false} {};

bool Pawn::isValidMove(Cell& start_cell, Cell& end_cell, Chessboard& board) const {
   unsigned int start_row = start_cell.getRow(), start_col = start_cell.getCol();
   unsigned int end_row = end_cell.getRow(), end_col = end_cell.getCol();

   if (getColour() == Colour::white) {
      if (board.getPiece(end_cell)) {
         // if there is a piece, it has to move diagonally
         return start_row + 1 == end_row && (start_col + 1 == end_col || start_col - 1 == end_col);
      } else {
         // if there isn't a piece, it has to move forward of one or two cell
         bool one_step = start_row + 1 == end_row;
         bool two_steps = !hasMoved() && start_row + 2 == end_row && !board.getPiece(Cell{start_row + 1, end_col});
         return start_col == end_col && (one_step || two_steps);
      }
   } else {
      if (board.getPiece(end_cell)) {
         // if there is a piece, it has to move diagonally
         return start_row - 1 == end_row && (start_col + 1 == end_col || start_col - 1 == end_col);
      } else {
         // if there isn't a piece, it has to move forward of one or two cell
         bool one_step = start_row - 1 == end_row;
         bool two_steps = !hasMoved() && start_row - 2 == end_row && !board.getPiece(Cell{start_row - 1, end_col});
         return start_col == end_col && (one_step || two_steps);      
      }
   }
   
   return false;
}

ostream& Pawn::print_piece(ostream& of) const {
   char c = getColour() == Colour::white ? tolower(PAWN_LETTER) : toupper(PAWN_LETTER);
   of << c; 
   return of;
}

char Pawn::getLetter() const {
   return getColour() == Colour::white ? tolower(PAWN_LETTER) : toupper(PAWN_LETTER);
}

bool Pawn::hasMoved() const {
   return _hasMoved;
}

void Pawn::set_has_moved(bool b) {
   _hasMoved = b;
}