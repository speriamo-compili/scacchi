#include "..\header_files\Computer.h"
#include <random>
#include <chrono>
#include <cassert>

Computer::Computer(const Colour c, Chessboard &b) : Player{c}, board{b} {
    // initialize random seed
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    srand(seed);
};

std::array<Cell, 2> Computer::get_move() const {
    Cell *start_cell;
    std::vector<Cell> valid_cells;

    do {    
        int n_pieces = board.get_pieces_on_board(this->get_colour());
        unsigned int k = rand() % n_pieces;

        for (unsigned int i = 0, j = 0; i < Chessboard::N_PIECES; i++) {
            Cell *cell = board.get_cell_from_piece_id(i, this->get_colour());
            if (cell) {
                if (j == k) {
                    start_cell = cell; 
                    break;
                } 
                j++;
            }
        }

        Piece *piece_to_move = board.getPiece(*start_cell);
        assert(piece_to_move);

        for (unsigned int r = 0; r < Chessboard::N_ROWS; r++) {
            for (unsigned int c = 0; c < Chessboard::N_COLS; c++) {
                Cell *end_cell = new Cell{r,c};
                
                bool is_valid_move = piece_to_move->isValidMove(*start_cell, *end_cell, board);
                bool is_castling = board.is_castling(start_cell, end_cell, piece_to_move);
                bool is_en_passant = board.is_en_passant(*start_cell, *end_cell, piece_to_move);

                if (is_valid_move || is_castling || is_en_passant) {
                    valid_cells.push_back(*end_cell);
                }
            }
        }

    } while(valid_cells.size() == 0);

    unsigned int ind_end_cell = rand() % valid_cells.size();
    Cell end_cell = valid_cells[ind_end_cell];
    return std::array<Cell,2> {*start_cell, end_cell};
}
