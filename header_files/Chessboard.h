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
        void capture_piece();
        void set_has_moved(Piece *piece_moved);
        void undo_move(Cell *start_cell, Cell *end_cell, Piece *piece_moved);
        bool isInCheck(const Colour c);
        bool canMove(const Colour c);
        void checkPromotion(Cell& end_cell);
        void set_possible_en_passant(Cell& start_cell, Cell& end_cell, Piece *piece_moved);
        bool is_en_passant(Cell& start_cell, Cell& end_cell, Piece *piece_to_move);
        void undo_en_passant(Cell *start_cell, Cell *end_cell, Cell& cell_pawn_to_capture, Piece *piece_moved);
        bool is_castling(Cell *start_cell, Cell *end_cell, Piece *piece_to_move);
        
        unsigned int get_pieces_on_board(const Colour c) const;
        Cell* get_cell_from_piece_id(unsigned int id, const Colour c) const;

        // TO DELETE
        void print_vec(Colour c);

    private:
        void move(Cell *start_cell, Cell *end_cell, Piece *piece_to_move);
        
        Piece *board[N_ROWS][N_COLS], *last_piece_captured;
        vector<Cell*> white_pieces, black_pieces;
        unsigned int white_pieces_on_board, black_pieces_on_board;  
        Cell *en_passant_cell; // cell where the pawn has to go for en-passant
};

ostream& operator<<(ostream& os, const Chessboard& board);
#endif