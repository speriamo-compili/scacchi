/**
 * @file Player.cpp
 * @author Samuel Piron
 */

#include "../header_files/Player.h"

Player::Player(const Colour c) : colour(c) {};
//get the colour of the piece
Colour Player::get_colour() const {
    return colour;
}