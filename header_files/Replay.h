#ifndef REPLAY_H
#define REPLAY_H
#include "Piece.h"
#include <fstream>

class Replay {
    private:
        Chessboard board;
        string input_file_name, output_file_name;
        ifstream input_file;
        ofstream output_file;
        bool print_on_file;
        Colour colour_to_move;

        void print_board();
        void end_game(); 

    public:

        Replay(const string &in);
        Replay(const string &in, const string &out);

        void print();

};

#endif