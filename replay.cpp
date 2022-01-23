#include <iostream>
#include "header_files/Replay.h"

int main(int argc, char *argv[]) {
    if (argc < 3 || argc > 4) {
        cout << "You have to pass one or two command line arguments!\n" 
             << "- first argument -> v (print on video) or f (print on file)\n"
             << "- second argument -> name of the log file\n" 
             << "- third argument (optional) -> name of the output file\n"
             << "If the third argument is not given, the output is printed on video.\n"; 
        return 0;
    }

    if (argc == 3) {
        Replay r(argv[2]);
        r.print();
    } else if (argc == 4) {
        Replay r(argv[2], argv[3]);
        r.print();
    }
    return 0;
}