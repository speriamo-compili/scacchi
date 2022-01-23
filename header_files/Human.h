/**
 * @file Human.h
 * @author Simone Corrò
 */

#ifndef HUMAN_H
#define HUMAN_H

#include "Player.h"
/*
    class that implements the human player
*/
class Human : public Player {
    public:
        Human(const Colour c, Chessboard &board);
        std::array<Cell, 2> get_move() const override;
        bool ask_for_draw();

    private:
        Chessboard &board;
};

std::string to_lower(const std::string &s);

#endif