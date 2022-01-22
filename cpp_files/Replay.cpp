#include "..\header_files\Replay.h"
#include <chrono>
#include <thread>

Replay::Replay(const string &in) : input_file_name{in}, print_on_file{false} {};

Replay::Replay(const string &in, const string &out) : input_file_name{in}, output_file_name{out}, print_on_file{true} {};

void Replay::print_board() {
    if (print_on_file) {
        output_file << board << "\n";
    } else {
        cout << board << "\n";
    }
}

void Replay::end_game() {
    cout << string(5, HORIZONTAL_SEP) << " Game ended " << string(5,HORIZONTAL_SEP) << "\n\n"; 
    
    if (board.get_pieces_on_board(Colour::white) == 1 && board.get_pieces_on_board(Colour::black) == 1) {
        cout << "It's impossible to force the checkmate with only two kings left.\nThe game ended in a draw.\n";
        return;
    }

    bool can_move = board.canMove(colour_to_move);
    if (!can_move) {
        cout << (colour_to_move == Colour::white ? "White" : "Black") << " in ";
        if (board.isInCheck(colour_to_move)) {
            cout << "checkmate.\n" << (colour_to_move == Colour::white ? "Black" : "White") << " wins.\n";
        } else {
            cout << "stalemate.\nThe game ended in a draw.\n";
        }
    } else {
        cout << "The game has reached its maximum number of moves.\n";
    }

    return;
}

void Replay::print() {
    input_file.open(input_file_name);    
    if (!input_file) {
        cout << "Input file not found\n";
        return;
    }
    if (print_on_file) {
        output_file.open(output_file_name);    
        if (!output_file) {
            cout << "Output file not found\n";
            return;
        }
    }
    
    print_board();
    int move = 1;
    colour_to_move = Colour::white;
    while (!input_file.eof()) {
        if (!print_on_file) {
            // std::this_thread::sleep_for(std::chrono::seconds(1));
        }
        
        string start, end;
        input_file >> start >> end;

        // blank line
        if (start == "" && end == "") {
            continue;
        }

        Cell start_cell(start), end_cell(end);
        board.move(start_cell, end_cell);
        cout << string(5, HORIZONTAL_SEP) << " Move " << move++ << " " << string(5,HORIZONTAL_SEP) << "\n\n"; 
        print_board();
        colour_to_move = colour_to_move == Colour::white ? Colour::black : Colour::white;
    }

    end_game();
    input_file.close();
    output_file.close();
}

