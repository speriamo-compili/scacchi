/**
 * @file Chessboard.h
 * @author Lorenzo Cazzador
 */

#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include "Cell.h"

#include <vector>

// forward declaration
class Piece;
enum class Colour : short;

/*
    Class that implement a Chessboard with normal moves, special moves and check control
*/
class Chessboard {
    public:
        // exception thrown when a piece cannot make that move
        class invalid_move{};
        // exception thrown when the state of the game is not valid, for example when a king is not found
        class invalid_state{};
        // exception thrown when a move puts your king in check
        class invalid_move_king_on_check{};

        static constexpr unsigned int N_ROWS = 8;
        static constexpr unsigned int N_COLS = 8;
        static constexpr unsigned int N_PIECES = 16;

        static constexpr unsigned int ID_FIRST_ROOK = 0;
        static constexpr unsigned int ID_FIRST_KNIGHT = 1;
        static constexpr unsigned int ID_FIRST_BISHOP = 2;
        static constexpr unsigned int ID_QUEEN = 3;
        static constexpr unsigned int ID_KING = 4;
        static constexpr unsigned int ID_SECOND_BISHOP = 5;
        static constexpr unsigned int ID_SECOND_KNIGHT = 6;
        static constexpr unsigned int ID_SECOND_ROOK = 7;
        static constexpr unsigned int ID_FIRST_PAWN = 8;

        Chessboard();
        ~Chessboard();

        /* 
            returns a pointer to the piece in the given cell
        */
        Piece* get_piece(const Cell& c) const;
        /* 
            returns a pointer to the piece in the given cell
        */
        void set_piece(const Cell& cell, Piece* p);

        /*
            main function to move a piece
        */
        void move(Cell& start_cell, Cell& end_cell);
        /*
            function called when a piece is captured
        */
        void capture_piece();
        /*
            function to set has_moved variables
        */
        void set_has_moved(Piece *piece_moved);
        /*
            function to undo a move
        */
        void undo_move(Cell *start_cell, Cell *end_cell, Piece *piece_moved);
        /*
            function to control if the king of colour c is in check
        */
        bool is_in_check(const Colour c);
        /*
            function to control if colour c can move
        */
        bool can_move(const Colour c);
        /*
            function to promote a pawn into queen
        */
        void check_promotion(Cell& end_cell);
        /*
            function to set a possible en passant
        */
        void set_possible_en_passant(Cell& start_cell, Cell& end_cell, Piece *piece_moved);
        /*
            function to check if the move is an en passant move
        */
        bool is_en_passant(Cell& start_cell, Cell& end_cell, Piece *piece_to_move);
        /*
            function to undo the en passant
        */
        void undo_en_passant(Cell *start_cell, Cell *end_cell, Cell& cell_pawn_to_capture, Piece *piece_moved);
        /*
            function to check if the move is a castling
        */
        bool is_castling(Cell *start_cell, Cell *end_cell, Piece *piece_to_move);
        
        /*
            function to get the number of pieces of colour c on the board
        */
        unsigned int get_pieces_on_board(const Colour c) const;
        Cell* get_cell_from_piece_id(unsigned int id, const Colour c) const;
        Piece* get_last_piece_captured();
        
        std::string to_string();

        // disable assignment operator
        Chessboard &operator=(const Chessboard &) = delete;

    private:
        void move(Cell *start_cell, Cell *end_cell, Piece *piece_to_move);
        
        Piece *board[N_ROWS][N_COLS], *last_piece_captured;
        std::vector<Cell*> white_pieces, black_pieces;
        unsigned int white_pieces_on_board, black_pieces_on_board;  
        Cell *en_passant_cell; // cell where the pawn has to go for en-passant
};

std::ostream& operator<<(std::ostream& os, const Chessboard& board);
#endif