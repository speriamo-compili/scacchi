#ifndef QUEEN_H
#define QUEEN_H
#include "Piece.h"

class Queen : public Piece {
    Queen(colour c);
    ~Queen() {};

    bool isValidMove(Cell& start_cell, Cell& end_cell) const override;
    char print_piece() const override;
};

#endif