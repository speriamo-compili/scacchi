/**
 * @file Player.h
 * @author Samuel Piron
 */

#ifndef PLAYER_H
#define PLAYER_H

#include "Piece.h"
#include "Cell.h"

#include <array>

class Player {
    private:
        Colour colour;
    
    public:
        Player(const Colour c);

        virtual std::array<Cell, 2> get_move() const = 0;
        Colour get_colour() const;
};

#endif