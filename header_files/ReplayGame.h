/**
 * @file ReplayGame.h
 * @author Samuel Piron
 */

#ifndef REPLAY_H
#define REPLAY_H

#include "Piece.h"

#include <fstream>

class ReplayGame {
    private:
        Chessboard board;
        std::string input_file_name, output_file_name;
        std::ifstream input_file;
        std::ofstream output_file;
        bool print_on_file;
        Colour colour_to_move;

        void print_board();
        void end_game(const std::string &result, const std::string &reason); 

    public:

        ReplayGame(const std::string &in);
        ReplayGame(const std::string &in, const std::string &out);
        ~ReplayGame();
        
        void print();

};

#endif