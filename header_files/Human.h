#ifndef HUMAN_H
#define HUMAN_H
#include "Player.h"

class Human : public Player {
    public:
        Human(const Colour c, Chessboard &board);
        std::array<Cell, 2> get_move() const override;

    private:
        Chessboard &board;
};

#endif