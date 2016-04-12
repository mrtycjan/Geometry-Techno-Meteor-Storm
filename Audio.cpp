#include "Audio.h"

Audio::Audio(void)
{
    if(!mainMusic.openFromFile("data/spaceship.ogg"))
        return;

    if(!gameMusic.openFromFile("data/soundtrack.ogg"))
        return;

    mainMusic.setLoop(true);
    gameMusic.setLoop(true);

    mainMusic.setVolume(80);
    gameMusic.setVolume(80);

}
void Audio::playGame()
{
    gameMusic.play();
}

void Audio::playMain()
{
    mainMusic.play();
}

void Audio::stopGame()
{
    gameMusic.stop();
}

void Audio::stopMain()
{
    mainMusic.stop();
}

