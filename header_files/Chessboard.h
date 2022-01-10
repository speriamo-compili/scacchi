#ifndef CHESSBOARD_H
#define CHESSBOARD_H
#include "Cell.h"
#include <vector>

enum class Colour;
class Piece;

class Chessboard {
    public:
        class InvalidMove{};
        class InvalidState{};
        class InvalidMove_KingOnCheck{};

        static constexpr unsigned int N_ROWS = 8;
        static constexpr unsigned int N_COLS = 8;
        static constexpr unsigned int N_PIECES = 16;
        static constexpr unsigned int ID_KING = 4;

        Chessboard();
        ~Chessboard();

        Piece* getPiece(const Cell& c) const;
        void setPiece(const Cell& cell, Piece* p);

        void move(Cell& start_cell, Cell& end_cell);
        void undo_move(Cell *start_cell, Cell *end_cell, Piece *piece_moved);
        bool isInCheck(const Colour c);
        bool canMove(const Colour c);
        void checkPromotion(Cell& end_cell);
    
    private:
        void move(Cell *start_cell, Cell *end_cell, Piece *piece_to_move);
        
        Piece *board[N_ROWS][N_COLS], *last_piece_captured;
        vector<Cell*> white_pieces, black_pieces;
};

ostream& operator<<(ostream& os, const Chessboard& board);
#endif