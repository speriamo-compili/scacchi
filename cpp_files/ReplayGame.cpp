/**
 * @file ReplayGame.cpp
 * @author Samuel Piron
 */

#include "../header_files/ReplayGame.h"

#include <chrono>
#include <thread>

ReplayGame::ReplayGame(const std::string &in) : input_file_name{in}, print_on_file{false} {};

ReplayGame::ReplayGame(const std::string &in, const std::string &out) : input_file_name{in}, output_file_name{out}, print_on_file{true} {};

void ReplayGame::print_board() {
    if (print_on_file) {
        output_file << board << "\n";
    } else {
        std::cout << board << "\n";
    }
}

void ReplayGame::end_game(const std::string &result, const std::string &reason) {
    std::cout << "───── Game ended ─────\n\n"; 

    if (reason == "Wcm") {
        std::cout << "White in checkmate.\n";
    } else if (reason == "Bcm") {
        std::cout << "Black in checkmate.\n";
    } else if (reason == "Wsm") {
        std::cout << "White in stalemate.\n";
    } else if (reason == "Bsm") {
        std::cout << "Black in stalemate.\n";
    } else if (reason == "rvsR") {
        std::cout << "It's impossible to force the checkmate with only two kings left.\n";
    } else if (reason == "50m") {
        std::cout << "In the last 50 moves, no player has captured a piece or moved a pawn.\n";
    } else if (reason == "max") {
        std::cout << "The game has reached its maximum number of moves.\n";
    } else if (reason == "3r") {
        std::cout << "The same board configuration occurred 3 times. The player decided to end the game in a draw.\n";
    } else if (reason == "5r") {
        std::cout << "The same board configuration occurred 5 times.\n";
    } else {
        std::cout << "The game was interrupted before the end.\n";
    }

    if (result == "D") {
        std::cout << "The game ended in a draw.\n";
    } else if (result == "W") {
        std::cout << "White wins.\n";
    } else if (result == "B") {
        std::cout << "Black wins.\n";
    }
    
    return;
}

void ReplayGame::print() {
    input_file.open(input_file_name);    
    if (!input_file) {
        std::cout << "Input file not found\n";
        return;
    }
    if (print_on_file) {
        output_file.open(output_file_name);    
        if (!output_file) {
            std::cout << "Output file not found\n";
            return;
        }
    }
    
    print_board();
    int move = 1;
    colour_to_move = Colour::white;
    std::string start, end;

    while (!input_file.eof()) {
        if (!print_on_file) {
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
        
        input_file >> start >> end;

        // blank line
        if (start == "" && end == "") {
            continue;
        }

        // end of the game
        if (start.size() == 1) {
            break;
        }

        Cell start_cell(start), end_cell(end);
        board.move(start_cell, end_cell);
        std::cout << "───── Move " << move++ << " ─────\n\n"; 
        print_board();
        colour_to_move = colour_to_move == Colour::white ? Colour::black : Colour::white;
    }


    end_game(start, end);
    input_file.close();
    output_file.close();
}

ReplayGame::~ReplayGame() {
    if (input_file.is_open()) {
        input_file.close();
    }
    if (output_file.is_open()) {
        output_file.close();
    }
}