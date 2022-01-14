#include "..\header_files\Player.h"

Player::Player(const Colour c) : colour(c) {};

Colour Player::get_colour() const {
    return colour;
}
