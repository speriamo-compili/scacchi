#include "..\header_files\Computer.h"
#include <time.h>
#include <cassert>

Computer::Computer(const Colour c, Chessboard &b) : Player{c}, board{b} {};

std::array<Cell, 2> Computer::get_move() const {
    // initialize random seed
    srand(time(NULL));
    Cell start_cell;
    std::vector<Cell> valid_cells;
    
    do {    
        unsigned int k = rand() % board.get_pieces_on_board(this->get_colour()); 
        for (unsigned int i = 0, j = 0; i < Chessboard::N_PIECES; i++) {
            Cell *cell = board.get_cell_from_piece_id(i, this->get_colour());
            if (cell) {
                if (j == k) {
                    start_cell = *cell; 
                    break;
                } 
                j++;
            }
        }
        Piece *piece_to_move = board.getPiece(start_cell);
        assert(piece_to_move);
        for (unsigned int r = 0; r < Chessboard::N_ROWS; r++) {
            for (unsigned int c = 0; c < Chessboard::N_COLS; c++) {
                Cell cell = Cell{r,c};
                if (piece_to_move->isValidMove(start_cell, cell, board)) {
                    valid_cells.push_back(cell);
                }
            }
        }
    } while(valid_cells.size() == 0);

    unsigned int ind_end_cell = rand() % valid_cells.size();
    Cell end_cell = valid_cells[ind_end_cell];
    return std::array<Cell,2> {start_cell, end_cell};
}
