#ifndef PAWN_H
#define PAWN_H
#include "Piece.h"

class Pawn : public Piece {
    Pawn(colour c);
    ~Pawn() {};

    bool isValidMove(Cell& start_cell, Cell& end_cell) const override;
    char print_piece() const override;
};

#endif