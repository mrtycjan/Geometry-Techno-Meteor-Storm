#pragma once
#include <SFML/Graphics.hpp>

class Player
{
public:
    sf::CircleShape ship;

    float velocity, speedLess, accelerate, accLimit, Rotate;
    long long int lifes, score;

    Player(void);

};
