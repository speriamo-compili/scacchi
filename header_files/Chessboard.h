#ifndef CHESSBOARD_H
#define CHESSBOARD_H
#include "Cell.h"
#include <vector>

enum class Colour;
class Piece;

class Chessboard {
    private:
        Piece* board[8][8];
        vector<Cell> white_pieces, black_pieces;
        
    public:
        class InvalidMove{};

        Chessboard();
        ~Chessboard();

        void move(Cell& start_cell, Cell& end_cell);
        Piece* getPiece(const Cell& c) const;
        bool isInCheck(const Colour c) const;

        // TO BE DELETED
        void setPiece(Piece* p, const Cell& cell);
};

ostream& operator<<(ostream& os, const Chessboard& board);
#endif