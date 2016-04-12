#include "Player.h"

Player::Player(void)
{
    ship.setPointCount(3);
    ship.setRadius(12);
    ship.setPosition(400-12, 580);
    ship.setOutlineThickness(-1.f);
    ship.setOutlineColor(sf::Color::Cyan);
    ship.setFillColor(sf::Color::Transparent);
    ship.setOrigin(12, 12);

    velocity = 0;
    Rotate = 300;
    accLimit = 100;
    speedLess = 30;
    accelerate = 10;
    lifes = 3;
    score = 0;
}
