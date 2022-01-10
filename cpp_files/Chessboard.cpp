#include "..\header_files\Chessboard.h"
#include "..\header_files\Piece.h"
#include "..\header_files\Bishop.h"
#include "..\header_files\King.h"
#include "..\header_files\Knight.h"
#include "..\header_files\Pawn.h"
#include "..\header_files\Queen.h"
#include "..\header_files\Rook.h"

Chessboard::Chessboard() {
    for (unsigned int r = 0; r < 8; r++) {
        for (unsigned int c = 0; c < 8; c++) {
            board[r][c] = nullptr;
        }
    }

    board[0][0] = new Rook(Colour::white, 0);
    board[0][1] = new Knight(Colour::white, 1);
    board[0][2] = new Bishop(Colour::white, 2);
    board[0][3] = new Queen(Colour::white, 3);
    board[0][4] = new King(Colour::white, 4);
    board[0][5] = new Bishop(Colour::white, 5);
    board[0][6] = new Knight(Colour::white, 6);
    board[0][7] = new Rook(Colour::white, 7);
    for (unsigned int c = 0; c < 8; c++) {
        board[1][c] = new Pawn(Colour::white, 8 + c);
    }

    white_pieces.resize(16);
    for (unsigned int i = 0; i < 16; i++) {
        white_pieces[i] = Cell{i / 8, i % 8};
    }
    cout << endl;




    board[7][0] = new Rook(Colour::black, 0);
    board[7][1] = new Knight(Colour::black, 1);
    board[7][2] = new Bishop(Colour::black, 2);
    board[7][3] = new Queen(Colour::black, 3);
    board[7][4] = new King(Colour::black, 4);
    board[7][5] = new Bishop(Colour::black, 5);
    board[7][6] = new Knight(Colour::black, 6);
    board[7][7] = new Rook(Colour::black, 7);
    for (unsigned int c = 0; c < 8; c++) {
        board[6][c] = new Pawn(Colour::black, 8 + c);
    }
}

Chessboard::~Chessboard() {
    for (unsigned int r = 0; r < 8; r++) {
        for (unsigned int c = 0; c < 8; c++) {
            delete board[r][c];
            board[r][c] = nullptr;
        }
    }
}

void Chessboard::move(Cell& start_cell, Cell& end_cell) {
    bool canMove = board[start_cell.getRow()][start_cell.getCol()]->isValidMove(start_cell, end_cell, *this);
    if (canMove) {
        board[end_cell.getRow()][end_cell.getCol()] = board[start_cell.getRow()][start_cell.getCol()]; 
        board[start_cell.getRow()][start_cell.getCol()]  = nullptr;
    } else {
        throw InvalidMove();
    }
}

Piece* Chessboard::getPiece(const Cell& c) const {
    return board[c.getRow()][c.getCol()];
}

bool Chessboard::isInCheck(const Colour c) const {
    // check if the king of colour c is in check

    // cerco la posizione del re
    // white_pieces[4] 
    return false;
}

// TO BE DELETED
void Chessboard::setPiece(Piece* p, const Cell& c) {
    board[c.getRow()][c.getCol()] = p;
}

ostream& operator<<(ostream& os, const Chessboard& b) {
    for (unsigned int r = 8; r > 0; r--) {
        os << r << " ";
        for (unsigned int c = 0; c < 8; c++) {
            Piece* p = b.getPiece(Cell{r - 1, c});
            if (p)
                os << *p;
            else    
                os << " ";
        }
        os << endl;
    }
    os << endl << "  ";
    for (unsigned int i = 0; i < 8; i++) {
        os << char('A' + i);
    }
    os << endl;
    return os;
}