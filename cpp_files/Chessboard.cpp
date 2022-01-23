/**
 * @file Chessboard.h
 * @author Lorenzo Cazzador
 */

#include "../header_files/Chessboard.h"
#include "../header_files/Piece.h"
#include "../header_files/Bishop.h"
#include "../header_files/King.h"
#include "../header_files/Knight.h"
#include "../header_files/Pawn.h"
#include "../header_files/Queen.h"
#include "../header_files/Rook.h"

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

Piece* Chessboard::get_piece(const Cell& c) const {
    return board[c.get_row()][c.get_col()];
}

void Chessboard::set_piece(const Cell& c, Piece* p) {
    board[c.get_row()][c.get_col()] = p;
}

void Chessboard::move(Cell& start_cell, Cell& end_cell) {
    Cell *start_cell_pointer = new Cell{start_cell.get_row(), start_cell.get_col()}; 
    Cell *end_cell_pointer = new Cell{end_cell.get_row(), end_cell.get_col()}; 
    Piece *piece_to_move = get_piece(start_cell); 

    bool can_move = piece_to_move->is_valid_move(start_cell, end_cell, *this);
    bool en_passant = is_en_passant(start_cell, end_cell, piece_to_move);
    bool castling = is_castling(start_cell_pointer, end_cell_pointer, piece_to_move);

    if (can_move) {
        move(start_cell_pointer, end_cell_pointer, piece_to_move);

        if (is_in_check(piece_to_move->get_colour())) {
            // the move can't be done
            undo_move(start_cell_pointer, end_cell_pointer, piece_to_move);
            throw invalid_move_king_on_check();
        }

        en_passant_cell = nullptr;
        set_possible_en_passant(start_cell, end_cell, piece_to_move);
        check_promotion(end_cell);

    } else if (en_passant) {
        move(start_cell_pointer, end_cell_pointer, piece_to_move);
        Cell cell_pawn_to_capture = Cell{end_cell.get_row() + (piece_to_move->get_colour() == Colour::white ? -1 : 1), end_cell.get_col()};
        last_piece_captured = get_piece(cell_pawn_to_capture);
        set_piece(cell_pawn_to_capture, nullptr); 
        capture_piece();
        en_passant_cell = nullptr;

        if (is_in_check(piece_to_move->get_colour())) {
            // the move can't be done - undo_en_passant
            undo_en_passant(start_cell_pointer, end_cell_pointer, cell_pawn_to_capture, piece_to_move);
            throw invalid_move_king_on_check();
        }

    } else if (castling) {
        int delta_col = start_cell.get_col() - end_cell.get_col();
        move(start_cell_pointer, end_cell_pointer, piece_to_move);
        Cell *start_cell_rook, *end_cell_rook;
        if (delta_col == -2) {
            start_cell_rook = new Cell{start_cell.get_row(), start_cell.get_col() + 3};
            end_cell_rook = new Cell{end_cell.get_row(), end_cell.get_col() - 1};
        } else if (delta_col == 2) {
            start_cell_rook = new Cell{start_cell.get_row(), start_cell.get_col() - 4};
            end_cell_rook = new Cell{end_cell.get_row(), end_cell.get_col() + 1};
        }
        Piece *rook = get_piece(*start_cell_rook);
        move(start_cell_rook, end_cell_rook, rook);
    } else {
        throw invalid_move();
    }

    set_has_moved(piece_to_move);
}

void Chessboard::capture_piece() {
    if (last_piece_captured && last_piece_captured->get_colour() == Colour::white) {
        white_pieces[last_piece_captured->get_id()] = nullptr;
        white_pieces_on_board--;
    } else if (last_piece_captured) {
        black_pieces[last_piece_captured->get_id()] = nullptr;
        black_pieces_on_board--;
    }
}

void Chessboard::move(Cell *start_cell, Cell *end_cell, Piece *piece_to_move) {
    last_piece_captured = get_piece(*end_cell);
    set_piece(*end_cell, piece_to_move);
    set_piece(*start_cell, nullptr);
    
    if (piece_to_move->get_colour() == Colour::white) {
        white_pieces[piece_to_move->get_id()] = end_cell;
    } else {
        black_pieces[piece_to_move->get_id()] = end_cell;
    }
    
    capture_piece();
}

void Chessboard::set_has_moved(Piece *piece_moved) {
    const char piece_letter = piece_moved->get_letter();

    if (piece_letter == 'p' || piece_letter == 'P') dynamic_cast<Pawn*>(piece_moved)->set_has_moved(true); 
    if (piece_letter == 'r' || piece_letter == 'R') dynamic_cast<King*>(piece_moved)->set_has_moved(true); 
    if (piece_letter == 't' || piece_letter == 'T') dynamic_cast<Rook*>(piece_moved)->set_has_moved(true); 
}

void Chessboard::undo_move(Cell *start_cell, Cell *end_cell, Piece *piece_moved) {
    set_piece(*start_cell, piece_moved);
    set_piece(*end_cell, last_piece_captured);
    if (piece_moved->get_colour() == Colour::white) {
        white_pieces[piece_moved->get_id()] = start_cell;
    } else {
        black_pieces[piece_moved->get_id()] = start_cell;
    }

    if (last_piece_captured && last_piece_captured->get_colour() == Colour::white) {
        white_pieces[last_piece_captured->get_id()] = end_cell;
        white_pieces_on_board++;
    } else if (last_piece_captured){
        black_pieces[last_piece_captured->get_id()] = end_cell;
        black_pieces_on_board++;
    }
}

bool Chessboard::is_in_check(const Colour c) {
    // check if the king of colour c is in check

    // take the cell of the king of colour c
    Cell *king_cell = (c == Colour::white ? white_pieces[ID_KING] : black_pieces[ID_KING]);

    // assert 
    if (!king_cell) {
        throw invalid_state{};
    }

    // check if a piece of opposite colour can capture the king
    for (int i = 0; i < N_PIECES; i++) {
        Cell *cell = (c == Colour::white ? black_pieces[i] : white_pieces[i]);
        if (cell) {
            Piece *p = get_piece(*cell);
            if (p->is_valid_move(*cell, *king_cell, *this)) {
                return true;
            }
        }
    }

    return false;
}

bool Chessboard::can_move(const Colour colour) {
    // check if the player with colour c can move
    for (int i = 0; i < N_PIECES; i++) {
        Cell *start_cell = (colour == Colour::white ? white_pieces[i] : black_pieces[i]);
        if (start_cell) {
            Piece *piece_to_move = get_piece(*start_cell);
            for (unsigned int r = 0; r < N_ROWS; r++) {
                for (unsigned int c = 0; c < N_COLS; c++) {
                    Cell *end_cell = new Cell{r,c};
                    if (piece_to_move->is_valid_move(*start_cell, *end_cell, *this)) {
                        
                        move(start_cell, end_cell, piece_to_move);

                        bool can_move = !is_in_check(colour);

                        undo_move(start_cell, end_cell, piece_to_move);

                        if (can_move) {
                            return true;
                        }

                    }
                }
            }
        }
    }
    return false;
}

void Chessboard::check_promotion(Cell& end_cell) {
    Piece *piece_moved = get_piece(end_cell);
    if (piece_moved->get_letter() == 'P' && end_cell.get_row() == 0) {
        set_piece(end_cell, new Queen(Colour::black, piece_moved->get_id()));
    }
    if (piece_moved->get_letter() == 'p' && end_cell.get_row() == 7) {
        set_piece(end_cell, new Queen(Colour::white, piece_moved->get_id()));
    }
}

void Chessboard::set_possible_en_passant(Cell& start_cell, Cell& end_cell, Piece *piece_moved) {
    bool is_two_cells_move = (start_cell.get_col() == end_cell.get_col() && (start_cell.get_row() - end_cell.get_row() == 2));
    if (piece_moved->get_letter() == 'P' && is_two_cells_move) {
        en_passant_cell = new Cell{end_cell.get_row() + 1, end_cell.get_col()};
    }

    is_two_cells_move = (start_cell.get_col() == end_cell.get_col() && (start_cell.get_row() - end_cell.get_row() == -2));
    if (piece_moved->get_letter() == 'p' && is_two_cells_move) {
        en_passant_cell = new Cell{end_cell.get_row() - 1, end_cell.get_col()};
    }
}

bool Chessboard::is_en_passant(Cell& start_cell, Cell& end_cell, Piece *piece_to_move) {
    bool is_diagonal_move = (start_cell.get_row() - end_cell.get_row() == 1) && abs(static_cast<int>(start_cell.get_col()) - static_cast<int>(end_cell.get_col())) == 1;
    if (piece_to_move->get_letter() == 'P' && is_diagonal_move && en_passant_cell && end_cell == *en_passant_cell) {
        return true;
    }

    is_diagonal_move = (start_cell.get_row() - end_cell.get_row()) == -1 && abs(static_cast<int>(start_cell.get_col()) - static_cast<int>(end_cell.get_col())) == 1;
    if (piece_to_move->get_letter() == 'p' && is_diagonal_move && en_passant_cell && end_cell == *en_passant_cell) {
        return true;
    }

    return false;
}

void Chessboard::undo_en_passant(Cell *start_cell, Cell *end_cell, Cell& cell_pawn_to_capture, Piece *piece_moved) {
    set_piece(*start_cell, piece_moved);
    set_piece(*end_cell, nullptr);
    set_piece(cell_pawn_to_capture, last_piece_captured);

    if (piece_moved->get_colour() == Colour::white) {
        white_pieces[piece_moved->get_id()] = start_cell;
    } else {
        black_pieces[piece_moved->get_id()] = start_cell;
    }

    Cell *pointer_cell_pawn_to_capture = new Cell{cell_pawn_to_capture.get_row(), cell_pawn_to_capture.get_col()};
    if (last_piece_captured && last_piece_captured->get_colour() == Colour::white) {
        white_pieces[last_piece_captured->get_id()] = pointer_cell_pawn_to_capture;
    } else if (last_piece_captured){
        black_pieces[last_piece_captured->get_id()] = pointer_cell_pawn_to_capture;
    }

    en_passant_cell = end_cell;
}

bool Chessboard::is_castling(Cell *start_cell, Cell *end_cell, Piece *piece_to_move) {
    assert(start_cell && end_cell && piece_to_move);

    bool is_king = piece_to_move->get_letter() == 'r' || piece_to_move->get_letter() == 'R';
    bool same_row = start_cell->get_row() == end_cell->get_row();
    if (!is_king || !same_row) {
        return false;
    }
    
    int delta_col = start_cell->get_col() - end_cell->get_col();
    bool king_has_moved = dynamic_cast<King*>(piece_to_move)->has_moved();
    
    // castling short
    if (!king_has_moved && delta_col == -2) {
        Piece *rook = get_piece(Cell{start_cell->get_row(), start_cell->get_col() + 3});
        // the rook isn't in the right place   
        if (!rook) {
            return false;
        } 
        bool right_rook = (piece_to_move->get_letter() == 'r' && rook->get_letter() == 't') || 
                          (piece_to_move->get_letter() == 'R' && rook->get_letter() == 'T');     
        if (!right_rook) {
            return false;
        }
        bool rook_has_moved = dynamic_cast<Rook*>(rook)->has_moved();
        if (rook_has_moved) {
            return false;
        }
        // check if there aren't pieces between the king and the rook 
        // and if the king is in check in these cells
        bool king_in_check = false;
        for (unsigned int i = 1; i <= 2; i++) {
            Cell cell = Cell{start_cell->get_row(), start_cell->get_col() + i};
            if (!get_piece(cell)) {
                move(start_cell, end_cell, piece_to_move);
                if (is_in_check(piece_to_move->get_colour())) {
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
        Piece *rook = get_piece(Cell{start_cell->get_row(), start_cell->get_col() - 4});
        // the rook isn't in the right place        
        if (!rook) {
            return false;
        } 
        bool right_rook = (piece_to_move->get_letter() == 'r' && rook->get_letter() == 't') || 
                          (piece_to_move->get_letter() == 'R' && rook->get_letter() == 'T');     
        if (!right_rook) {
            return false;
        }
        bool rook_has_moved = dynamic_cast<Rook*>(rook)->has_moved();
        if (rook_has_moved) {
            return false;
        }
        // check if there aren't pieces between the king and the rook 
        // and if the king is in check in these cells
        bool king_in_check = false;
        for (unsigned int i = 1; i <= 2; i++) {
            Cell cell = Cell{start_cell->get_row(), start_cell->get_col() - i};
            if (!get_piece(cell)) {
                move(start_cell, end_cell, piece_to_move);
                if (is_in_check(piece_to_move->get_colour())) {
                    king_in_check |= true; 
                }
                undo_move(start_cell, end_cell, piece_to_move);
            } else {
                return false;
            }
        }
        // check if there is a piece to the right of the rook (where the king doesn't go) 
        if (get_piece(Cell{start_cell->get_row(), start_cell->get_col() - 3})) {
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

Piece* Chessboard::get_last_piece_captured() {
    return last_piece_captured;
}

string Chessboard::to_string() {
    string res = "";
    for (unsigned int r = 0; r < Chessboard::N_ROWS; r++) {
        for (unsigned int c = 0; c < Chessboard::N_COLS; c++) {
            Piece* p = get_piece(Cell{r, c});
            if (p)
                res += p->get_letter();
            else    
                res += " ";
        }
    }
    return res;
}

ostream& operator<<(ostream& os, const Chessboard& b) {
    const string HORIZONTAL_SIDE = "─";
    const string VERTICAL_SIDE = "│";
    const string UP_LEFT_ANGLE = "┌";
    const string UP_RIGHT_ANGLE = "┐";
    const string DOWN_LEFT_ANGLE = "└";
    const string DOWN_RIGHT_ANGLE = "┘";

    os << "  " << UP_LEFT_ANGLE << "────────" << UP_RIGHT_ANGLE << endl;
    for (unsigned int r = Chessboard::N_ROWS; r > 0; r--) {
        os << r << " " << VERTICAL_SIDE;
        for (unsigned int c = 0; c < Chessboard::N_COLS; c++) {
            Piece* p = b.get_piece(Cell{r - 1, c});
            if (p)
                os << *p;
            else    
                os << " ";
        }
        os << VERTICAL_SIDE << endl;
    }
    os << "  " << DOWN_LEFT_ANGLE << "────────" << DOWN_RIGHT_ANGLE << endl << "   ";
    for (unsigned int i = 0; i < Chessboard::N_COLS; i++) {
        os << char('A' + i);
    }
    os << endl;
    return os;
}