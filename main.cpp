#include <iostream>
#include "header_files\Chessboard.h"
using namespace std;

// ostream& operator<< (ostream& os, Cell& c) {
//     os << "{" << c.getRow() << "," << c.getCol() << "}";
//     return os;
// }

int main() {
    // for(int i = 0; i < 8; i++) {
    //     for(int j = 0; j < 8; j++) {
    //         string s = string(1, 'a'+i) + string(1, '1'+j); 
    //         Cell c{s};
    //         vector<Cell> v;
    //         King k{Piece::colour::white};
    //         for(int r = 0; r < 8; r++) {
    //             for (int m = 0; m < 8; m++) {
    //                 string t = string(1, 'a'+r) + string(1, '1'+m);
    //                 Cell ce{t};
    //                 if (k.isValidMove(c, ce)) {
    //                     v.push_back(ce);
    //                 }
    //             }
    //         }
    //         cout << c << " -> ";
    //         for (Cell & x : v)
    //             cout << x << " ";
    //         cout << "\n"; 
    //     ;
    // }
    Chessboard b{};
    b.print_board();
    // Piece *p = new Bishop{Piece::colour::white};
    // cout << *p << "\n";
}