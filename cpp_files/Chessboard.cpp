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

    // board[0][0] = new Rook(Colour::white);
    // board[0][1] = new Knight(Colour::white);
    // board[0][2] = new Bishop(Colour::white);
    // board[0][3] = new Queen(Colour::white);
    // board[0][4] = new King(Colour::white);
    // board[0][5] = new Bishop(Colour::white);
    // board[0][6] = new Knight(Colour::white);
    // board[0][7] = new Rook(Colour::white);
    // for (unsigned int c = 0; c < 8; c++) {
    //     board[1][c] = new Pawn(Colour::white);
    // }

    // board[7][0] = new Rook(Colour::black);
    // board[7][1] = new Knight(Colour::black);
    // board[7][2] = new Bishop(Colour::black);
    // board[7][3] = new Queen(Colour::black);
    // board[7][4] = new King(Colour::black);
    // board[7][5] = new Bishop(Colour::black);
    // board[7][6] = new Knight(Colour::black);
    // board[7][7] = new Rook(Colour::black);
    // for (unsigned int c = 0; c < 8; c++) {
    //     board[6][c] = new Pawn(Colour::black);
    // }
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