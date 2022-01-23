/**
 * @file Game.h
 * @author Samuel Piron
 */

#ifndef GAME_H
#define GAME_H

#include "Chessboard.h"
#include "Player.h"

#include <random>
#include <map>

class Game {
    private:
        Chessboard board;
        Player *p1, *p2;
        bool current_turn; // true -> p1's turn, false -> p2's turn
        bool is_cc_game; 
        unsigned int n_moves;
        unsigned int stalemate_counter; //it counts the stalemate
        std::ofstream log;
        std::map<std::string, int> previous_boards;
    
        void alternate_turn(); //when is pc turn or player turn
        bool is_game_over(); //when the game finishes
        std::array<Colour, 2> get_random_colours();
        void print_log(const std::string &str);
        void update_stalemate_counter(std::array<Cell, 2> move);
        void update_previous_board();

    public:
        static constexpr unsigned int MAX_MOVES_CC_GAME = 500;
        static constexpr unsigned int FIFTY_MOVES = 50;
        static constexpr unsigned int THREEFOLD_REPETITION = 3;
        static constexpr unsigned int FIVEFOLD_REPETITION = 5;

        const std::string LOG_FILE = "log.txt";

        Game();
        Game(bool is_cc_game);
        void play();
        ~Game();
};

#endif