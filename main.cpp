#include <iostream>
#include <vector>
#include <cassert>
#include "header_files\Chessboard.h"
#include "header_files\Pawn.h"
#include "header_files\King.h"
using namespace std;

Chessboard board;    
Colour currentTurn;

bool isGameOver(Colour c) {
    bool can_move = board.canMove(c);
    if (!can_move) {
        cout << (c == Colour::white ? "bianco in" : "nero in");
        cout << (board.isInCheck(c) ? " scacco matto" : " patta");
        return true;
    }
    return false;
}

void alternateTurn() {
    currentTurn = (currentTurn == Colour::white ? Colour::black : Colour::white);
}

int main() {
    cout << board << "\n";
    currentTurn = Colour::white;

    do {
        string a, b;
        cout << "Inserisci mossa: ";
        cin >> a >> b;
        cout << a << " " << b << "\n\n";
        Cell start = Cell(a), end = Cell(b);
        assert(board.getPiece(start)->getColour() == currentTurn);
        board.move(start, end);
        cout << board << "\n";
        alternateTurn();
    } while(!isGameOver(currentTurn));


    // cout << board << "\n";
    // Cell a = Cell{"e1"}, b = Cell{"c1"};
    // board.move(a,b);
    // cout << board << "\n";
    
    // board.print_vec(Colour::white);
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