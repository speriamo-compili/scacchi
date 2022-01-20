#include <iostream>
#include "header_files/Game.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        cout << "You have to pass one command line argument! (pc or cc)";
        return 0;
    }
    string arg = argv[1];
    if (arg != "pc" && arg != "cc") {
        cout << "You have to pass one command line argument! (pc or cc)";
        return 0;
    }
    bool is_cc_game = arg == "cc";
    Game game(is_cc_game);
    game.play();
    return 0;
}