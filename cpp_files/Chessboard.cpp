#include "..\header_files\Chessboard.h"
#include "..\header_files\Piece.h"
#include "..\header_files\Bishop.h"
#include "..\header_files\King.h"
#include "..\header_files\Knight.h"
#include "..\header_files\Pawn.h"
#include "..\header_files\Queen.h"
#include "..\header_files\Rook.h"

Chessboard::Chessboard() {
    for (unsigned int r = 0; r < N_ROWS; r++) {
        for (unsigned int c = 0; c < N_COLS; c++) {
            board[r][c] = nullptr;
        }
    }

    black_pieces.resize(N_PIECES);
    white_pieces.resize(N_PIECES);

    board[3][3] = new King(Colour::white, 4);
    white_pieces[4] = new Cell{"d4"};

    board[7][0] = new King(Colour::black, 4);
    black_pieces[4] = new Cell{"a8"}; 

    board[1][5] = new Pawn(Colour::black, 9);
    black_pieces[9] = new Cell{"f2"};

    board[6][6] = new Pawn(Colour::white, 9);
    white_pieces[9] = new Cell{"g7"};

    // board[0][0] = new Rook(Colour::white, 0);
    // board[0][1] = new Knight(Colour::white, 1);
    // board[0][2] = new Bishop(Colour::white, 2);
    // board[0][3] = new Queen(Colour::white, 3);
    // board[0][4] = new King(Colour::white, 4);
    // board[0][5] = new Bishop(Colour::white, 5);
    // board[0][6] = new Knight(Colour::white, 6);
    // board[0][7] = new Rook(Colour::white, 7);
    // for (unsigned int c = 0; c < N_COLS; c++) {
    //     board[1][c] = new Pawn(Colour::white, 8 + c);
    // }

    // white_pieces.resize(N_PIECES);
    // for (unsigned int i = 0; i < N_PIECES; i++) {
    //     white_pieces[i] = new Cell{i / N_ROWS, i % N_COLS};
    // }

    // board[7][0] = new Rook(Colour::black, 0);
    // board[7][1] = new Knight(Colour::black, 1);
    // board[7][2] = new Bishop(Colour::black, 2);
    // board[7][3] = new Queen(Colour::black, 3);
    // board[7][4] = new King(Colour::black, 4);
    // board[7][5] = new Bishop(Colour::black, 5);
    // board[7][6] = new Knight(Colour::black, 6);
    // board[7][7] = new Rook(Colour::black, 7);
    // for (unsigned int c = 0; c < N_COLS; c++) {
    //     board[6][c] = new Pawn(Colour::black, 8 + c);
    // }

    // black_pieces.resize(N_PIECES);
    // for (unsigned int i = 0; i < N_PIECES; i++) {
    //     black_pieces[i] = new Cell{N_ROWS - 1 - (i / N_ROWS), i % N_COLS};
    // }
}

Chessboard::~Chessboard() {
    for (unsigned int r = 0; r < N_ROWS; r++) {
        for (unsigned int c = 0; c < N_COLS; c++) {
            delete board[r][c];
            board[r][c] = nullptr;
        }
    }
}

Piece* Chessboard::getPiece(const Cell& c) const {
    return board[c.getRow()][c.getCol()];
}

void Chessboard::setPiece(const Cell& c, Piece* p) {
    board[c.getRow()][c.getCol()] = p;
}

void Chessboard::move(Cell& start_cell, Cell& end_cell) {
    Piece *piece_to_move = getPiece(start_cell); 
    bool canMove = piece_to_move->isValidMove(start_cell, end_cell, *this);
    if (canMove) {
        Cell *start_cell_pointer = new Cell{start_cell.getRow(), start_cell.getCol()}; 
        Cell *end_cell_pointer = new Cell{end_cell.getRow(), end_cell.getCol()}; 
        move(start_cell_pointer, end_cell_pointer, piece_to_move);

        if (isInCheck(piece_to_move->getColour())) {
            // the move can't be done
            undo_move(start_cell_pointer, end_cell_pointer, piece_to_move);
            throw InvalidMove_KingOnCheck();
        }

        checkPromotion(end_cell);
    } else {
        throw InvalidMove();
    }
}

void Chessboard::move(Cell *start_cell, Cell *end_cell, Piece *piece_to_move) {
    last_piece_captured = getPiece(*end_cell);
    setPiece(*end_cell, piece_to_move);
    setPiece(*start_cell, nullptr);
    
    if (piece_to_move->getColour() == Colour::white) {
        white_pieces[piece_to_move->getId()] = end_cell;
    } else {
        black_pieces[piece_to_move->getId()] = end_cell;
    }
}

void Chessboard::undo_move(Cell *start_cell, Cell *end_cell, Piece *piece_moved) {
    setPiece(*start_cell, piece_moved);
    setPiece(*end_cell, last_piece_captured);
    if (piece_moved->getColour() == Colour::white) {
        white_pieces[piece_moved->getId()] = start_cell;
    } else {
        black_pieces[piece_moved->getId()] = start_cell;
    }
}

bool Chessboard::isInCheck(const Colour c) {
    // check if the king of colour c is in check

    // take the cell of the king of colour c
    Cell *king_cell = (c == Colour::white ? white_pieces[ID_KING] : black_pieces[ID_KING]);
    // assert 
    if (!king_cell) {
        throw InvalidState{};
    }

    // check if a piece of opposite colour can capture the king
    for (int i = 0; i < N_PIECES; i++) {
        Cell *cell = (c == Colour::white ? black_pieces[i] : white_pieces[i]);
        if (cell) {
            Piece *p = getPiece(*cell);
            if (p->isValidMove(*cell, *king_cell, *this)) {
                return true;
            }
        }
    }

    return false;
}

bool Chessboard::canMove(const Colour colour) {
    // check if the player with colour c can move
    for (int i = 0; i < 16; i++) {
        Cell *start_cell = (colour == Colour::white ? white_pieces[i] : black_pieces[i]);
        if (start_cell) {
            Piece *piece_to_move = getPiece(*start_cell);
            for (unsigned int r = 0; r < N_ROWS; r++) {
                for (unsigned int c = 0; c < N_COLS; c++) {
                    Cell *end_cell = new Cell{r,c};
                    if (piece_to_move->isValidMove(*start_cell, *end_cell, *this)) {

                        move(start_cell, end_cell, piece_to_move);

                        bool canMove = !isInCheck(colour);

                        undo_move(start_cell, end_cell, piece_to_move);

                        if (canMove) {
                            return true;
                        }

                    }
                }
            }
        }
    }
    return false;
}

void Chessboard::checkPromotion(Cell& end_cell) {
    Piece *piece_moved = getPiece(end_cell);
    if (piece_moved->getLetter() == 'P' && end_cell.getRow() == 0) {
        setPiece(end_cell, new Queen(Colour::black, piece_moved->getId()));
    }
    if (piece_moved->getLetter() == 'p' && end_cell.getRow() == 7) {
        setPiece(end_cell, new Queen(Colour::white, piece_moved->getId()));
    }
}


ostream& operator<<(ostream& os, const Chessboard& b) {
    for (unsigned int r = Chessboard::N_ROWS; r > 0; r--) {
        os << r << " ";
        for (unsigned int c = 0; c < Chessboard::N_COLS; c++) {
            Piece* p = b.getPiece(Cell{r - 1, c});
            if (p)
                os << *p;
            else    
                os << " ";
        }
        os << endl;
    }
    os << endl << "  ";
    for (unsigned int i = 0; i < Chessboard::N_COLS; i++) {
        os << char('A' + i);
    }
    os << endl;
    return os;
}

