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

    board[0][0] = new Rook(Piece::colour::black);
    board[0][1] = new Knight(Piece::colour::black);
    board[0][2] = new Bishop(Piece::colour::black);
    board[0][3] = new Queen(Piece::colour::black);
    board[0][4] = new King(Piece::colour::black);
    board[0][5] = new Bishop(Piece::colour::black);
    board[0][6] = new Knight(Piece::colour::black);
    board[0][7] = new Rook(Piece::colour::black);
    for (unsigned int c = 0; c < 8; c++) {
        board[1][c] = new Pawn(Piece::colour::black);
    }

    board[7][0] = new Rook(Piece::colour::white);
    board[7][1] = new Knight(Piece::colour::white);
    board[7][2] = new Bishop(Piece::colour::white);
    board[7][3] = new Queen(Piece::colour::white);
    board[7][4] = new King(Piece::colour::white);
    board[7][5] = new Bishop(Piece::colour::white);
    board[7][6] = new Knight(Piece::colour::white);
    board[7][7] = new Rook(Piece::colour::white);
    for (unsigned int c = 0; c < 8; c++) {
        board[6][c] = new Pawn(Piece::colour::white);
    }
}

Chessboard::~Chessboard() {
    for (int r = 0; r < 8; r++) {
        for (int c = 0; c < 8; c++) {
            delete board[r][c];
            board[r][c] = nullptr;
        }
    }
}

void Chessboard::move(Cell& start_cell, Cell& end_cell) {
    bool canMove = board[start_cell.getRow()][start_cell.getCol()]->isValidMove(start_cell, end_cell);
    if (canMove) {
        board[end_cell.getRow()][end_cell.getCol()] = board[start_cell.getRow()][start_cell.getCol()]; 
        board[start_cell.getRow()][start_cell.getCol()]  = nullptr;
    } else {
        throw InvalidMove();
    }
}

void Chessboard::print_board() const {
    for (int r = 0; r < 8; r++) {
        for (int c = 0; c < 8; c++) {
            if (board[r][c])
                cout << *board[r][c];
            else    
                cout << " ";
        }
        cout << "\n";
    }
}