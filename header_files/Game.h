#ifndef GAME_H
#define GAME_H
#include "Chessboard.h"
#include "Player.h"
#include <random>

class Game {
    private:
        Chessboard board;
        Player *p1, *p2;
        bool current_turn; // true -> p1's turn, false -> p2's turn
        bool is_cc_game; 
        unsigned int n_moves;
        ofstream log;
    
        void alternate_turn();
        bool is_game_over();
        std::array<Colour, 2> get_random_colours();
        void print_log(const string &str);

    public:
        static constexpr unsigned int MAX_MOVES_CC_GAME = 500;
        const string LOG_FILE = "log.txt";

        Game();
        Game(bool is_cc_game);
        void play();
        ~Game();
};

#endif