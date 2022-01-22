#include <iostream>
#include "header_files/Game.h"

void print_error() {
    cout << "You have to pass one command line argument! (pc or cc)\n" 
         << "- pc = player vs computer\n" 
         << "- cc = computer vs computer\n";
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        print_error();
        return 0;
    }
    string arg = argv[1];
    if (arg != "pc" && arg != "cc") {
        print_error();
        return 0;
    }
    bool is_cc_game = arg == "cc";
    Game game(is_cc_game);
    game.play();
    return 0;
}