#ifndef CHESSBOARD_H
#define CHESSBOARD_H
#include "Cell.h"
#include "Piece.h"

class Chessboard {
    private:
        Piece* board[8][8];
    public:
        class InvalidMove{};

        Chessboard();
        ~Chessboard();

        void move(Cell& start_cell, Cell& end_cell);

        friend ostream& operator<<(ostream& os, const Chessboard& board);
};

#endif