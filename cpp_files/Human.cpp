#include "..\header_files\Human.h"

Human::Human(const Colour c, Chessboard &b) : Player{c}, board{b} {};

std::array<Cell, 2> Human::get_move() const {
    bool valid_cells;
    Cell start_cell, end_cell;
    do {
        std::cout << "Enter the next move (" << (this->get_colour() == Colour::white ? "white" : "black") << "): ";
        std::string start, end;
        std::cin >> start >> end;
        valid_cells = true;

        if (start == "XX" && end == "XX") {
            cout << "\n" << board << "\n";
            valid_cells = false;
        } else {
            try {
                start_cell = Cell{start};
            } catch (Cell::InvalidCell) {
                cout << "The first cell is invalid.\n";
                valid_cells = false;
            }

            try {
                end_cell = Cell{end};
            } catch (Cell::InvalidCell) {
                cout << "The second cell is invalid.\n";
                valid_cells = false;
            }

            if (valid_cells) {
                // check if the start cell contains a piece of this player 
                Piece *piece_to_move = board.getPiece(start_cell);
                if (!piece_to_move || piece_to_move->getColour() != this->get_colour()) {
                    cout << "The start cell doesn't contain a " << this->get_colour() << " piece.\n";
                    valid_cells = false;
                }
            }
        }
    } while(!valid_cells);

    return std::array<Cell, 2>{start_cell, end_cell};
}