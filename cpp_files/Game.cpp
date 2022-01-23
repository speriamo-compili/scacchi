#include "../header_files/Game.h"
#include "../header_files/Computer.h"
#include "../header_files/Human.h"
#include <time.h>

// default game is human vs computer
Game::Game() : Game(false) {};

Game::Game(bool cc_game) : is_cc_game{cc_game} {
    std::array<Colour, 2> colours = get_random_colours();
    
    if (is_cc_game) {
        p1 = new Computer(colours[0], board);
        p2 = new Computer(colours[1], board);
    } else {
        p1 = new Human(colours[0], board);
        p2 = new Computer(colours[1], board);
    }
    current_turn = colours[0] == Colour::white;
    n_moves = 0;
    stalemate_counter = 0;
}

std::array<Colour, 2> Game::get_random_colours() {
    // initialize random seed
    srand(time(NULL));
    bool p1_white = rand() % 2;
    std::array<Colour, 2> res;
    if (p1_white) {
        res = {Colour::white, Colour::black};
    } else {
        res = {Colour::black, Colour::white};
    }
    return res;
}

void Game::print_log(const string &str) {
    log << str;
}

void Game::alternate_turn() {
    current_turn = !current_turn;
}

void Game::update_stalemate_counter(std::array<Cell, 2> move) {
    Piece *piece_moved = board.get_piece(move[1]);
    bool pawn_moved = piece_moved && (piece_moved->get_letter() == 'P' || piece_moved->get_letter() == 'p');
    if (board.get_last_piece_captured() || pawn_moved) {
        stalemate_counter = 0;
    } else {
        stalemate_counter++;
    }
} 

void Game::update_previous_board() {
    previous_boards[board.to_string()]++;
}

bool Game::is_game_over() {
    // if only two kings are left, it's impossible to force the checkmate
    if (board.get_pieces_on_board(Colour::white) == 1 && board.get_pieces_on_board(Colour::black) == 1) {
        cout << "It's impossible to force the checkmate with only two kings left.\nThe game ended in a draw.\n";
        return true;
    }

    Colour current_colour = current_turn ? p1->get_colour() : p2->get_colour();
    bool can_move = board.can_move(current_colour);
    if (!can_move) {
        cout << (current_colour == Colour::white ? "White" : "Black") << " in ";
        if (board.is_in_check(current_colour)) {
            cout << "checkmate.\n" << (current_colour == Colour::white ? "Black" : "White") << " wins.\n";
        } else {
            cout << "stalemate.\nThe game ended in a draw.\n";
        }
        return true;
    }

    if (stalemate_counter >= FIFTY_MOVES) {
        cout << "In the last 50 moves, no player has captured a piece or moved a pawn. The game ended in a draw.\n";
        return true;
    }
    
    if (n_moves >= MAX_MOVES_CC_GAME) {
        cout << "The game has reached its maximum number of moves. (" << MAX_MOVES_CC_GAME << ")\n";
        return true;
    }

    if (previous_boards[board.to_string()] == THREEFOLD_REPETITION && !is_cc_game) {
        bool draw =  dynamic_cast<Human*>(p1)->ask_for_draw();
        if (draw) {
            cout << "The game ended in a draw.\n";
            return true;
        }
    }

    return false;
}

void Game::play() {
    log.open(LOG_FILE);

    do {
        std::array<Cell, 2> move;
        bool valid_move = true;

        do {
            if (current_turn) {
                move = p1->get_move();
            } else {
                move = p2->get_move();
            }

            try {
                board.move(move[0], move[1]);
                valid_move = true;
            } catch(const Chessboard::invalid_move& e) {
                if (!is_cc_game && current_turn) {
                    cout << "Invalid move.\n";
                }
                valid_move = false;
            } catch(const Chessboard::invalid_move_king_on_check& e) {
                if (!is_cc_game && current_turn) {
                    cout << "Invalid move: after this move, your king would be in check.\n";
                }
                valid_move = false;
            }

        } while (!valid_move);

        log << move[0] << " " << move[1] << "\n";
        n_moves++;
        update_stalemate_counter(move);
        update_previous_board();
        alternate_turn();
    } while(!is_game_over());

    log.close();
}

Game::~Game() {
    delete p1;
    p1 = nullptr;
    delete p2;
    p2 = nullptr;
}
