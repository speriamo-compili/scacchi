/**
 * @file replay.cpp
 * @author Lorenzo Cazzador
 */

#include "header_files/ReplayGame.h"

#include <iostream>

int main(int argc, char *argv[]) {
    if (argc < 3 || argc > 4) {
        std::cout << "You have to pass one or two command line arguments!\n" 
             << "- first argument -> v (print on video) or f (print on file)\n"
             << "- second argument -> name of the log file\n" 
             << "- third argument (optional) -> name of the output file\n"
             << "If the third argument is not given, the output is printed on video.\n"; 
        return 0;
    }

    if (argc == 3) {
        ReplayGame r(argv[2]);
        r.print();
    } else if (argc == 4) {
        ReplayGame r(argv[2], argv[3]);
        r.print();
    }
    return 0;
}