#include "..\header_files\Chessboard.h"
#include "..\header_files\Piece.h"
#include "..\header_files\Bishop.h"
#include "..\header_files\King.h"
#include "..\header_files\Knight.h"
#include "..\header_files\Pawn.h"
#include "..\header_files\Queen.h"
#include "..\header_files\Rook.h"
#include <assert.h>

Chessboard::Chessboard() {
    for (unsigned int r = 0; r < N_ROWS; r++) {
        for (unsigned int c = 0; c < N_COLS; c++) {
            board[r][c] = nullptr;
        }
    }

    board[0][0] = new Rook(Colour::white, ID_FIRST_ROOK);
    board[0][1] = new Knight(Colour::white, ID_FIRST_KNIGHT);
    board[0][2] = new Bishop(Colour::white, ID_FIRST_BISHOP);
    board[0][3] = new Queen(Colour::white, ID_QUEEN);
    board[0][4] = new King(Colour::white, ID_KING);
    board[0][5] = new Bishop(Colour::white, ID_SECOND_BISHOP);
    board[0][6] = new Knight(Colour::white, ID_SECOND_KNIGHT);
    board[0][7] = new Rook(Colour::white, ID_SECOND_ROOK);
    for (unsigned int c = 0; c < N_COLS; c++) {
        board[1][c] = new Pawn(Colour::white, ID_FIRST_PAWN + c);
    }

    white_pieces.resize(N_PIECES);
    white_pieces_on_board = N_PIECES;
    for (unsigned int i = 0; i < N_PIECES; i++) {
        white_pieces[i] = new Cell{i / N_ROWS, i % N_COLS};
    }

    board[7][0] = new Rook(Colour::black, ID_FIRST_ROOK);
    board[7][1] = new Knight(Colour::black, ID_FIRST_KNIGHT);
    board[7][2] = new Bishop(Colour::black, ID_FIRST_BISHOP);
    board[7][3] = new Queen(Colour::black, ID_QUEEN);
    board[7][4] = new King(Colour::black, ID_KING);
    board[7][5] = new Bishop(Colour::black, ID_SECOND_BISHOP);
    board[7][6] = new Knight(Colour::black, ID_SECOND_KNIGHT);
    board[7][7] = new Rook(Colour::black, ID_SECOND_ROOK);
    for (unsigned int c = 0; c < N_COLS; c++) {
        board[6][c] = new Pawn(Colour::black, ID_FIRST_PAWN + c);
    }

    black_pieces.resize(N_PIECES);
    black_pieces_on_board = N_PIECES;
    for (unsigned int i = 0; i < N_PIECES; i++) {
        black_pieces[i] = new Cell{N_ROWS - 1 - (i / N_ROWS), i % N_COLS};
    }
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
    Cell *start_cell_pointer = new Cell{start_cell.getRow(), start_cell.getCol()}; 
    Cell *end_cell_pointer = new Cell{end_cell.getRow(), end_cell.getCol()}; 
    Piece *piece_to_move = getPiece(start_cell); 

    bool canMove = piece_to_move->isValidMove(start_cell, end_cell, *this);
    bool en_passant = is_en_passant(start_cell, end_cell, piece_to_move);
    bool castling = is_castling(start_cell_pointer, end_cell_pointer, piece_to_move);

    if (canMove) {
        move(start_cell_pointer, end_cell_pointer, piece_to_move);

        if (isInCheck(piece_to_move->getColour())) {
            // the move can't be done
            undo_move(start_cell_pointer, end_cell_pointer, piece_to_move);
            throw InvalidMove_KingOnCheck();
        }

        en_passant_cell = nullptr;
        set_possible_en_passant(start_cell, end_cell, piece_to_move);
        checkPromotion(end_cell);

    } else if (en_passant) {
        move(start_cell_pointer, end_cell_pointer, piece_to_move);
        Cell cell_pawn_to_capture = Cell{end_cell.getRow() + (piece_to_move->getColour() == Colour::white ? -1 : 1), end_cell.getCol()};
        last_piece_captured = getPiece(cell_pawn_to_capture);
        setPiece(cell_pawn_to_capture, nullptr); 
        capture_piece();
        en_passant_cell = nullptr;

        if (isInCheck(piece_to_move->getColour())) {
            // the move can't be done - undo_en_passant
            undo_en_passant(start_cell_pointer, end_cell_pointer, cell_pawn_to_capture, piece_to_move);
            throw InvalidMove_KingOnCheck();
        }

    } else if (castling) {
        int delta_col = start_cell.getCol() - end_cell.getCol();
        move(start_cell_pointer, end_cell_pointer, piece_to_move);
        Cell *start_cell_rook, *end_cell_rook;
        if (delta_col == -2) {
            start_cell_rook = new Cell{start_cell.getRow(), start_cell.getCol() + 3};
            end_cell_rook = new Cell{end_cell.getRow(), end_cell.getCol() - 1};
        } else if (delta_col == 2) {
            start_cell_rook = new Cell{start_cell.getRow(), start_cell.getCol() - 4};
            end_cell_rook = new Cell{end_cell.getRow(), end_cell.getCol() + 1};
        }
        Piece *rook = getPiece(*start_cell_rook);
        move(start_cell_rook, end_cell_rook, rook);
    } else {
        throw InvalidMove();
    }

    set_has_moved(piece_to_move);
}

void Chessboard::capture_piece() {
    if (last_piece_captured && last_piece_captured->getColour() == Colour::white) {
        white_pieces[last_piece_captured->getId()] = nullptr;
        white_pieces_on_board--;
    } else if (last_piece_captured) {
        black_pieces[last_piece_captured->getId()] = nullptr;
        black_pieces_on_board--;
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
    
    capture_piece();
}

void Chessboard::set_has_moved(Piece *piece_moved) {
    const char piece_letter = piece_moved->getLetter();

    if (piece_letter == 'p' || piece_letter == 'P') dynamic_cast<Pawn*>(piece_moved)->set_has_moved(true); 
    if (piece_letter == 'r' || piece_letter == 'R') dynamic_cast<King*>(piece_moved)->set_has_moved(true); 
    if (piece_letter == 't' || piece_letter == 'T') dynamic_cast<Rook*>(piece_moved)->set_has_moved(true); 
}

void Chessboard::undo_move(Cell *start_cell, Cell *end_cell, Piece *piece_moved) {
    setPiece(*start_cell, piece_moved);
    setPiece(*end_cell, last_piece_captured);
    if (piece_moved->getColour() == Colour::white) {
        white_pieces[piece_moved->getId()] = start_cell;
    } else {
        black_pieces[piece_moved->getId()] = start_cell;
    }

    if (last_piece_captured && last_piece_captured->getColour() == Colour::white) {
        white_pieces[last_piece_captured->getId()] = end_cell;
        white_pieces_on_board++;
    } else if (last_piece_captured){
        black_pieces[last_piece_captured->getId()] = end_cell;
        black_pieces_on_board++;
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
    for (int i = 0; i < N_PIECES; i++) {
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

void Chessboard::set_possible_en_passant(Cell& start_cell, Cell& end_cell, Piece *piece_moved) {
    bool is_two_cells_move = (start_cell.getCol() == end_cell.getCol() && (start_cell.getRow() - end_cell.getRow() == 2));
    if (piece_moved->getLetter() == 'P' && is_two_cells_move) {
        en_passant_cell = new Cell{end_cell.getRow() + 1, end_cell.getCol()};
    }

    is_two_cells_move = (start_cell.getCol() == end_cell.getCol() && (start_cell.getRow() - end_cell.getRow() == -2));
    if (piece_moved->getLetter() == 'p' && is_two_cells_move) {
        en_passant_cell = new Cell{end_cell.getRow() - 1, end_cell.getCol()};
    }
}

bool Chessboard::is_en_passant(Cell& start_cell, Cell& end_cell, Piece *piece_to_move) {
    bool is_diagonal_move = (start_cell.getRow() - end_cell.getRow() == 1) && abs(static_cast<int>(start_cell.getCol()) - static_cast<int>(end_cell.getCol())) == 1;
    if (piece_to_move->getLetter() == 'P' && is_diagonal_move && en_passant_cell && end_cell == *en_passant_cell) {
        return true;
    }

    is_diagonal_move = (start_cell.getRow() - end_cell.getRow()) == -1 && abs(static_cast<int>(start_cell.getCol()) - static_cast<int>(end_cell.getCol())) == 1;
    if (piece_to_move->getLetter() == 'p' && is_diagonal_move && en_passant_cell && end_cell == *en_passant_cell) {
        return true;
    }

    return false;
}

void Chessboard::undo_en_passant(Cell *start_cell, Cell *end_cell, Cell& cell_pawn_to_capture, Piece *piece_moved) {
    setPiece(*start_cell, piece_moved);
    setPiece(*end_cell, nullptr);
    setPiece(cell_pawn_to_capture, last_piece_captured);

    if (piece_moved->getColour() == Colour::white) {
        white_pieces[piece_moved->getId()] = start_cell;
    } else {
        black_pieces[piece_moved->getId()] = start_cell;
    }

    Cell *pointer_cell_pawn_to_capture = new Cell{cell_pawn_to_capture.getRow(), cell_pawn_to_capture.getCol()};
    if (last_piece_captured && last_piece_captured->getColour() == Colour::white) {
        white_pieces[last_piece_captured->getId()] = pointer_cell_pawn_to_capture;
    } else if (last_piece_captured){
        black_pieces[last_piece_captured->getId()] = pointer_cell_pawn_to_capture;
    }

    en_passant_cell = end_cell;
}

bool Chessboard::is_castling(Cell *start_cell, Cell *end_cell, Piece *piece_to_move) {
    assert(start_cell && end_cell && piece_to_move);

    bool is_king = piece_to_move->getLetter() == 'r' || piece_to_move->getLetter() == 'R';
    bool same_row = start_cell->getRow() == end_cell->getRow();
    if (!is_king || !same_row) {
        return false;
    }
    
    int delta_col = start_cell->getCol() - end_cell->getCol();
    bool king_has_moved = dynamic_cast<King*>(piece_to_move)->hasMoved();
    
    // castling short
    if (!king_has_moved && delta_col == -2) {
        Piece *rook = getPiece(Cell{start_cell->getRow(), start_cell->getCol() + 3});
        // the rook isn't in the right place   
        if (!rook) {
            return false;
        } 
        bool right_rook = (piece_to_move->getLetter() == 'r' && rook->getLetter() == 't') || 
                          (piece_to_move->getLetter() == 'R' && rook->getLetter() == 'T');     
        if (!right_rook) {
            return false;
        }
        bool rook_has_moved = dynamic_cast<Rook*>(rook)->hasMoved();
        if (rook_has_moved) {
            return false;
        }
        // check if there aren't pieces between the king and the rook 
        // and if the king is in check in these cells
        bool king_in_check = false;
        for (unsigned int i = 1; i <= 2; i++) {
            Cell cell = Cell{start_cell->getRow(), start_cell->getCol() + i};
            if (!getPiece(cell)) {
                move(start_cell, end_cell, piece_to_move);
                if (isInCheck(piece_to_move->getColour())) {
                    king_in_check |= true; 
                }
                undo_move(start_cell, end_cell, piece_to_move);
            } else {
                return false;
            }
        }
        return !king_in_check;
    }

    // castling long
    if (!king_has_moved && delta_col == 2) {
        Piece *rook = getPiece(Cell{start_cell->getRow(), start_cell->getCol() - 4});
        // the rook isn't in the right place        
        if (!rook) {
            return false;
        } 
        bool right_rook = (piece_to_move->getLetter() == 'r' && rook->getLetter() == 't') || 
                          (piece_to_move->getLetter() == 'R' && rook->getLetter() == 'T');     
        if (!right_rook) {
            return false;
        }
        bool rook_has_moved = dynamic_cast<Rook*>(rook)->hasMoved();
        if (rook_has_moved) {
            return false;
        }
        // check if there aren't pieces between the king and the rook 
        // and if the king is in check in these cells
        bool king_in_check = false;
        for (unsigned int i = 1; i <= 2; i++) {
            Cell cell = Cell{start_cell->getRow(), start_cell->getCol() - i};
            if (!getPiece(cell)) {
                move(start_cell, end_cell, piece_to_move);
                if (isInCheck(piece_to_move->getColour())) {
                    king_in_check |= true; 
                }
                undo_move(start_cell, end_cell, piece_to_move);
            } else {
                return false;
            }
        }
        // check if there is a piece to the right of the rook (where the king doesn't go) 
        if (getPiece(Cell{start_cell->getRow(), start_cell->getCol() - 3})) {
            return false;
        }

        return !king_in_check;
    }

    return false;
}

unsigned int Chessboard::get_pieces_on_board(const Colour c) const {
    return c == Colour::white ? white_pieces_on_board : black_pieces_on_board;
}

Cell* Chessboard::get_cell_from_piece_id(unsigned int id, const Colour c) const {
    return c == Colour::white ? white_pieces[id] : black_pieces[id];
}



ostream& operator<<(ostream& os, const Chessboard& b) {
    // const char HORIZONTAL_SIDE = char(205);
    // const char VERTICAL_SIDE = char(186);
    // const char UP_LEFT_ANGLE = char(201);
    // const char UP_RIGHT_ANGLE = char(187);
    // const char DOWN_LEFT_ANGLE = char(200);
    // const char DOWN_RIGHT_ANGLE = char(188);
    const char HORIZONTAL_SIDE = char(196);
    const char VERTICAL_SIDE = char(179);
    const char UP_LEFT_ANGLE = char(218);
    const char UP_RIGHT_ANGLE = char(191);
    const char DOWN_LEFT_ANGLE = char(192);
    const char DOWN_RIGHT_ANGLE = char(217);

    os << "  " << UP_LEFT_ANGLE << string(8, HORIZONTAL_SIDE) << UP_RIGHT_ANGLE << endl;
    for (unsigned int r = Chessboard::N_ROWS; r > 0; r--) {
        os << r << " " << VERTICAL_SIDE;
        for (unsigned int c = 0; c < Chessboard::N_COLS; c++) {
            Piece* p = b.getPiece(Cell{r - 1, c});
            if (p)
                os << *p;
            else    
                os << " ";
        }
        os << VERTICAL_SIDE << endl;
    }
    os << "  " << DOWN_LEFT_ANGLE << string(8, HORIZONTAL_SIDE) << DOWN_RIGHT_ANGLE << endl << "   ";
    for (unsigned int i = 0; i < Chessboard::N_COLS; i++) {
        os << char('A' + i);
    }
    os << endl;
    return os;
}

// TO DELETE
void Chessboard::print_vec(Colour c) {
    if (c == Colour::white) {
        cout << "WHITE PIECES\n";
        for (int i = 0; i < N_PIECES; i++) {
            Cell *k = white_pieces[i]; 
            if (k) {
                cout << i << " -> " << "{" << k->getRow() << "," << k->getCol() << "}\n";
            }
        }
    } else {
        cout << "BLACK PIECES\n";
        for (int i = 0; i < N_PIECES; i++) {
            Cell *k = black_pieces[i]; 
            if (k) {
                cout << i << " -> " << "{" << k->getRow() << "," << k->getCol() << "}\n";
            }
        }
    }
}