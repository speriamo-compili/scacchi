/**
 * @file Human.cpp
 * @author Simone Corrò
 */

#include "../header_files/Human.h"

#include <iostream>

Human::Human(const Colour c, Chessboard &b) : Player{c}, board{b} {};

std::array<Cell, 2> Human::get_move() const {
    bool valid_cells;
    Cell start_cell, end_cell;
    do {
        std::cout << "Enter the next move (" << (this->get_colour() == Colour::white ? "white" : "black") << "): ";
        std::string start, end;
        std::cin >> start >> end;
        valid_cells = true;

        if (to_lower(start) == "xx" && to_lower(end) == "xx") {
            std::cout << "\n" << board << "\n";
            valid_cells = false;
        } else {
            try {
                start_cell = Cell{start};
            } catch (Cell::invalid_cell) {
                std::cout << "The first cell is invalid.\n";
                valid_cells = false;
            }

            try {
                end_cell = Cell{end};
            } catch (Cell::invalid_cell) {
                std::cout << "The second cell is invalid.\n";
                valid_cells = false;
            }

            if (valid_cells) {
                // check if the start cell contains a piece of this player 
                Piece *piece_to_move = board.get_piece(start_cell);
                if (!piece_to_move || piece_to_move->get_colour() != this->get_colour()) {
                    std::cout << "The start cell doesn't contain a " << this->get_colour() << " piece.\n";
                    valid_cells = false;
                }
            }
        }
    } while(!valid_cells);

    return std::array<Cell, 2>{start_cell, end_cell};
}

bool Human::ask_for_draw() {
    bool valid_ans = true;
    std::string ans;

    do {
        // La stessa configurazione della scacchiera si è presentata per 3 volte. Do you want to end the game in a draw? [y/n] 
        std::cout << "The same board configuration occurred 3 times.\nDo you want to end the game in a draw? [y/n] ";
        std::cin >> ans;
        valid_ans = true;
        
        if (to_lower(ans) != "y" && to_lower(ans) != "n") {
            std::cout << "You have to answer with 'y' or 'n'.\n";
            valid_ans = false;
        }

    } while(!valid_ans);

    return to_lower(ans) == "y";
}

std::string to_lower(const std::string &s) {
    std::string res = "";
    for (char c : s) {
        res += tolower(c);
    }
    return res;
}