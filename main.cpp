#include <iostream>
#include <vector>
#include "header_files\Chessboard.h"
#include "header_files\Knight.h"
#include "header_files\King.h"
using namespace std;

ostream& operator<< (ostream& os, Cell& c) {
    os << "{" << c.getRow() << "," << c.getCol() << "}";
    return os;
}

int main() {
    Chessboard b;
    cout << b;
    for(unsigned int i = 0; i < 8; i++) {
        for(unsigned int j = 0; j < 8; j++) {
            string s = string(1, 'a'+j) + string(1, '1'+i); 
            Cell c{s};
            vector<Cell> v;
            Knight bi{Colour::white};
            // unsigned int f = (j + 2 < 8 ? j+2 : j-2);
            // King *k = new King{Colour::black};
            // Cell a{i, f};
            // b.setPiece(k, a);
            for(unsigned int r = 0; r < 8; r++) {
                for (unsigned int m = 0; m < 8; m++) {
                    string t = string(1, 'a'+r) + string(1, '1'+m);
                    Cell ce{t};
                    if (bi.isValidMove(c, ce, b)) {
                        v.push_back(ce);
                    }
                }
            }
            // b.setPiece(nullptr, a);
            // cout << c << " -> re in " << a << " -> ";
            cout << c << " -> ";
            for (Cell & x : v)
                cout << x << " ";
            cout << "\n"; 
        }
    }
    // Piece *p = new Bishop{Colour::white};
    // cout << *p << "\n";
}