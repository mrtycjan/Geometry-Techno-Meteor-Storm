#pragma once

#include <SFML/Graphics.hpp>
#include <cmath>
#include <cstdlib>
#include <sstream>

#include "Player.h"
#include "Entity.h"
#include "Audio.h"

#define cyan sf::Color::Cyan
#define white sf::Color::White
#define red sf::Color::Red
#define M_PI 3.14159265359


class Engine
{
public:

    Engine(sf::RenderWindow &win);

    void runEngine();

private:

    sf::Vector2f windowSize;
    sf::RenderWindow *window;
    sf::Text info, game_over;
    sf::Font font;

    bool crash, gameOver;

    Player player;
    Entity entity;
    Audio gameAudio;

    void meteorControl(Entity &entities, float &delta_time);
    void playerControl(Player *player, float &delta_time, bool pressed);

    inline bool collision(Player &triangle, Entity &object);
    inline std::string toString(int number);

    std::string stringInfo, stringGameOver;

};
