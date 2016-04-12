#pragma once

#include <SFML/Graphics.hpp>

#include "Engine.h"
#include "Audio.h"

class Game
{
public:
    sf::RenderWindow window;

    Game(void);

    enum GameState {MENU, ENGINE, OVER, END};
    GameState state;

    void runGame();

private:
    sf::Vector2f windowSize;
    sf::ContextSettings winSet;
    sf::Font font;

    void start();
    void menu();


};
