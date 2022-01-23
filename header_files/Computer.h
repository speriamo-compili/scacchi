/**
 * @file Computer.h
 * @author Simone Corrò
 */

#ifndef COMPUTER_H
#define COMPUTER_H

#include "Player.h"
#include "Chessboard.h"

class Computer : public Player {
    public:
        Computer(const Colour c, Chessboard &board);
        std::array<Cell, 2> get_move() const override;

    private:
        Chessboard &board;
};

#endif