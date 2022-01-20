#include "..\header_files\Game.h"
#include "..\header_files\Computer.h"
#include "..\header_files\Human.h"
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

void Game::alternate_turn() {
    current_turn = !current_turn;
}

bool Game::is_game_over() {
    Colour current_colour = current_turn ? p1->get_colour() : p2->get_colour();
    bool can_move = board.canMove(current_colour);
    if (!can_move) {
        // TO FIX
        cout << (current_colour == Colour::white ? "bianco in" : "nero in");
        cout << (board.isInCheck(current_colour) ? " scacco matto" : " stallo");
        return true;
    }
    return false;
}

void Game::play() {
    do {
        cout << board << "\n";

        std::array<Cell, 2> move;
        if (current_turn) {
            move = p1->get_move();
        } else {
            move = p2->get_move();
        }

        board.move(move[0], move[1]);
        alternate_turn();
    } while(!is_game_over());
}

Game::~Game() {
    delete p1;
    p1 = nullptr;
    delete p2;
    p2 = nullptr;
}
