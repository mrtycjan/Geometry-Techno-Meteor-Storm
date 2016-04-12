#pragma once

#include <SFML/Audio.hpp>


class Audio
{
public:
    sf::Music mainMusic;
    sf::Music gameMusic;

    Audio(void);

    void playMain();
    void playGame();
    void stopMain();
    void stopGame();

};
