#ifndef HUMAN_H
#define HUMAN_H
#include "Player.h"

class Human : public Player {
    public:
        Human(const Colour c);
        std::array<Cell, 2> get_move() const override;
};

#endif