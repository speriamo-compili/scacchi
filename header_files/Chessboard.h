#ifndef CHESSBOARD_H
#define CHESSBOARD_H
#include "Cell.h"

class Piece;

class Chessboard {
    private:
        Piece* board[8][8];
    public:
        class InvalidMove{};

        Chessboard();
        ~Chessboard();

        void move(Cell& start_cell, Cell& end_cell);
        Piece* getPiece(const Cell& c) const;

        // TO BE DELETED
        void setPiece(Piece* p, const Cell& cell);
};

ostream& operator<<(ostream& os, const Chessboard& board);
#endif