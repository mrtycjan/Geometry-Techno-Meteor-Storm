#pragma once

#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <vector>

#define M 70

class Entity
{
public:
    int ile;
    int speed[M];
    float speedUp;

    sf::CircleShape meteor[M];
    sf::FloatRect meteorBox[M];

    Entity(void);

};
