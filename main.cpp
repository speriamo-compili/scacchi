#include <iostream>
#include <vector>
#include "header_files\Chessboard.h"
#include "header_files\Pawn.h"
#include "header_files\King.h"
using namespace std;

ostream& operator<< (ostream& os, Cell& c) {
    os << "{" << c.getRow() + 1 << "," << char('A' + c.getCol()) << "}";
    return os;
}

int main() {
    Chessboard board;    
    cout << board;

    Cell a = Cell{"e8"}, b = Cell{"c8"};
    board.move(a,b);

    cout << board;

    // cout << (b.isInCheck(Colour::black) ?  "nero scacco" : "nero non scacco") << endl;
    // cout << (!b.canMove(Colour::black) ? "nero scacco matto" : "nero non scacco matto") << endl;

    // cout << (b.isInCheck(Colour::white) ?  "bianco scacco" : "bianco non scacco") << endl;
    // cout << (!b.canMove(Colour::white) ? "bianco scacco matto" : "bianco non scacco matto") << endl;
}


// for(int i = 0; i < 8; i++) {
    // for(int j = 0; j < 8; j++) {
    //     string s = string(1, 'a'+j) + string(1, '1'+1); 
    //     Cell c{s};
    //     vector<Cell> v;
    //     Piece *p = b.getPiece(c);
        // int g, f;
        // if (i+2 < 8 && j+2 < 8) {
        //     g = i + 2;
        //     f = j + 2;
        // } else if (i-2 >= 0 && j-2 >= 0) {
        //     g = i - 2;
        //     f = j - 2;
        // } else if (i+2 < 8 && j-2 >= 0) {
        //     g = i + 2;
        //     f = j - 2;
        // } else if (i-2 >= 0 && j+2 < 8) {
        //     g = i - 2;
        //     f = j + 2;
        // } else cout << "ERRORE\n";
        
        // for(unsigned int r = 0; r < 8; r++) {
        //     for (unsigned int m = 0; m < 8; m++) {
        //         string t = string(1, 'a'+r) + string(1, '1'+m);
        //         Cell ce{t};
        //         if (p->isValidMove(c, ce, b)) {
        //             v.push_back(ce);
        //         }
        //     }
        // }
        // b.setPiece(nullptr, a);
        // cout << c << " -> re in " << a << " -> ";
    //     cout << c << " " << *p << " -> " << v.size() << " ";
    //     for (Cell & x : v)
    //         cout << x << " ";
    //     cout << "\n"; 
    // }
// }
// Piece *p = new Bishop{Colour::white};
// cout << *p << "\n";